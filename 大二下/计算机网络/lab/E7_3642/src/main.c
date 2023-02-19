#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>

#define BUFSIZE 65536
#define IPSIZE 4
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))	//���ڻ�ȡ��ǰ���鳤��
#define ARRAY_INIT    {0}

unsigned short int port = 1080;						//Ĭ�϶˿�1080
int daemon_mode = 0;								//�Ƿ���Ҫ�ػ�����
int auth_type;										//��֤���ͣ�Ĭ��Ϊ������֤��
char *arg_username;									//�û�����ѡ���û���+������֤��������ã�
char *arg_password;									//���루ѡ���û���+������֤��������ã�
FILE *log_file;										//��־�ļ��������Ĭ��Ϊstdout
pthread_mutex_t lock;							//����������������ͣ������߳�����������java��reentrantlock

enum socks					//ʹ��ʲô�汾��socket
{
	RESERVED = 0x00,
	VERSION4 = 0x04,
	VERSION5 = 0x05
};

enum socks_auth_methods		//��֤����
{
	NOAUTH = 0x00,			//������֤
	USERPASS = 0x02,		//�û���+����
	NOMETHOD = 0xff
};

enum socks_auth_userpass	//�û���+������֤״̬
{
	AUTH_OK = 0x00,
	AUTH_VERSION = 0x01,
	AUTH_FAIL = 0xff
};

enum socks_command			//ָ��
{
	CONNECT = 0x01
};

enum socks_command_type		//ָ������
{
	IP = 0x01,
	DOMAIN = 0x03
};

enum socks_status			//�׽���״̬
{
	OK = 0x00,
	FAILED = 0x05
};

//�βθ��������Ͳ�ȷ����֪ͨ�������ں�������ʱ������β����ͺ�ʵ�������Ƿ���ͬ��Ҳ������������
void log_message(const char *message, ...)
{
	if (daemon_mode)	//������ػ�����ģʽ��ֱ���˳�������
	{
		return;
	}

	char vbuffer[255];			//v��ͷ��һ���ǿɱ�ı���
	va_list args;				//typedef char* va_list
	va_start(args, message);	//va_start ���ڳ�ʼ��va_list���͵ı������ڶ������������һ�����ݸ���������֪�Ĺ̶���������ʡ�Ժ�֮ǰ�Ĳ���

	//ARRAY_SIZE���ã����Լ�ס
	vsnprintf(vbuffer, ARRAY_SIZE(vbuffer), message, args);		//��args����messgae����ʽд��vbuffer
	va_end(args);

	//׼����ӡʱ��
	time_t now;
	time(&now);
	char *date = ctime(&now);
	date[strlen(date) - 1] = '\0';

	pthread_t self = pthread_self();	//��ȡ��ǰ�߳�����pid

	//errno���ڼ�¼ϵͳ���һ�δ������
	if (errno != 0) {
		pthread_mutex_lock(&lock);
		//error���ڰѴ������ת��Ϊ��Ӧ�Ŀɶ�����
		fprintf(log_file, "[%s][%lu] Critical: %s - %s\n", date, self,
			vbuffer, strerror(errno));
		errno = 0;
		pthread_mutex_unlock(&lock);
	} else {
		fprintf(log_file, "[%s][%lu] Info: %s\n", date, self, vbuffer);
	}
	//������������еĶ�����ӡ��stdout��
	fflush(log_file);
}

//������ȡ��Ϣ�ĺ���
int readn(int fd, void *buf, int n)
{
	int nread, left = n;
	while (left > 0) {
		//read(int fd, void *buf, size_t count)
		//��fd��ָ���ļ�����count���ֽڵ�buf��ָ���ڴ���
		//���ػ�ֵΪʵ�ʶ�ȡ�����ֽ���, �������0, ��ʾ�ѵ����ļ�β�����޿ɶ�ȡ������
		//������count Ϊ0, ��read()���������ò�����0
		if ((nread = read(fd, buf, left)) == -1) {
			if (errno == EINTR || errno == EAGAIN) {
				continue;
			}
		} else {
			if (nread == 0) {
				return 0;
			} else {
				left -= nread;
				buf += nread;
			}
		}
	}
	return n;
}

//����д��Ϣ�ĺ���
int writen(int fd, void *buf, int n)
{
	int nwrite, left = n;
	while (left > 0) {
		//write(int fd, const void * buf, size_t count)
		//�Ѳ���buf��ָ���ڴ�д��count���ֽڵ������ŵ���ָ���ļ���
		//���˳��write()�᷵��ʵ��д����ֽ��������д�����ʱ�򷵻�-1������������errno��
		if ((nwrite = write(fd, buf, left)) == -1) {
			if (errno == EINTR || errno == EAGAIN) {
				continue;
			}
		} else {
			if (nwrite == n) {
				return 0;
			} else {
				left -= nwrite;
				buf += nwrite;
			}
		}
	}
	return n;
}

//���ڹر�socket���̵߳ĺ���
void app_thread_exit(int ret, int fd)
{
	//�ر�fd�ļ�
	//�˳�ret��ָ�߳�
	close(fd);
	pthread_exit((void *)&ret);
}

//��Ҫ���Ӻ���
int app_connect(int type, void *buf, unsigned short int portnum)
{
	int fd;
	struct sockaddr_in remote;
	char address[16];

	memset(address, 0, ARRAY_SIZE(address));

	if (type == IP)		//����ip��������
	{
		char *ip = (char *)buf;
		snprintf(address, ARRAY_SIZE(address), "%hhu.%hhu.%hhu.%hhu",
			 ip[0], ip[1], ip[2], ip[3]);
		memset(&remote, 0, sizeof(remote));
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = inet_addr(address);
		remote.sin_port = htons(portnum);

		fd = socket(AF_INET, SOCK_STREAM, 0);		//������ʽ�׽���

		//connect(SOCKET s, const struct sockaddr * name, int namelen)
		//������ָ��socket������
		//name��Ҫ���ӵ��׽��ֵ�ָ��
		//namelen��sockaddr�ṹ��ĳ���
		if (connect(fd, (struct sockaddr *)&remote, sizeof(remote)) < 0)	//�������ʧ��
		{
			log_message("connect() in app_connect");
			close(fd);
			return -1;
		}

		return fd;
		//domain��Ҫ����ͬip���֣���ͬ�ط�����Ҫ�Ƚ�������
	} else if (type == DOMAIN) {
		char portaddr[6];
		struct addrinfo *res;
		snprintf(portaddr, ARRAY_SIZE(portaddr), "%d", portnum);
		log_message("getaddrinfo: %s %s", (char *)buf, portaddr);
		//�ؼ����룺getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result)
		//�������ֵ���ַ�Լ����񵽶˿�������ת��
		//hostname��������/��ַ������ipv4�ĵ��ʮ���ơ�ipv6��16���ƴ���
		//service��Ҫô�Ƕ˿ںţ�Ҫô�����еķ������ƣ�����http��ftp
		//hints����ָ�룬������ĳ��ָ��addrinfo��ָ��
		//result��������ͨ��resultָ���������һ��ָ��addrinfo�ṹ�������ָ��
		int ret = getaddrinfo((char *)buf, portaddr, NULL, &res);
		if (ret == EAI_NODATA) {
			return -1;
		} else if (ret == 0) {
			struct addrinfo *r;
			for (r = res; r != NULL; r = r->ai_next) {
				fd = socket(r->ai_family, r->ai_socktype,
					    r->ai_protocol);
                if (fd == -1) {
                    continue;
                }
				ret = connect(fd, r->ai_addr, r->ai_addrlen);
				if (ret == 0) {
					freeaddrinfo(res);
					return fd;
                } else {
                    close(fd);
                }
			}
		}
		freeaddrinfo(res);
		return -1;
	}

    return -1;
}

//��ȡ�汾��
int socks_invitation(int fd, int *version)
{
	char init[2];

	//��fd��ָ���ļ����͵�init�ַ�������ȥ
	int nread = readn(fd, (void *)init, ARRAY_SIZE(init));
	if (nread == 2 && init[0] != VERSION5 && init[0] != VERSION4) {
        log_message("They send us %hhX %hhX", init[0], init[1]);
		log_message("Incompatible version!");
		app_thread_exit(0, fd);
	}
	log_message("Initial %hhX %hhX", init[0], init[1]);
	//��ð汾��
	*version = init[0];
	//����ʵ�����н����init[1]Ӧ����������/�߳���
	return init[1];
}

//ѡ��SOCK5����£���ȡ�û���
char *socks5_auth_get_user(int fd)
{
	unsigned char size;
	readn(fd, (void *)&size, sizeof(size));

	char *user = (char *)malloc(sizeof(char) * size + 1);
	readn(fd, (void *)user, (int)size);
	user[size] = 0;

	return user;
}

//ѡ��SOCK5����£���ȡ����
char *socks5_auth_get_pass(int fd)
{
	unsigned char size;
	readn(fd, (void *)&size, sizeof(size));

	char *pass = (char *)malloc(sizeof(char) * size + 1);
	readn(fd, (void *)pass, (int)size);
	pass[size] = 0;

	return pass;
}

//ѡ��SOCK5 + �û�������֤
int socks5_auth_userpass(int fd)
{
	char answer[2] = { VERSION5, USERPASS };
	writen(fd, (void *)answer, ARRAY_SIZE(answer));
	char resp;
	readn(fd, (void *)&resp, sizeof(resp));
	log_message("auth %hhX", resp);
	char *username = socks5_auth_get_user(fd);
	char *password = socks5_auth_get_pass(fd);
	log_message("l: %s p: %s", username, password);
	if (strcmp(arg_username, username) == 0
	    && strcmp(arg_password, password) == 0) {
		char answer[2] = { AUTH_VERSION, AUTH_OK };
		writen(fd, (void *)answer, ARRAY_SIZE(answer));
		free(username);
		free(password);
		return 0;
	} else {
		char answer[2] = { AUTH_VERSION, AUTH_FAIL };
		writen(fd, (void *)answer, ARRAY_SIZE(answer));
		free(username);
		free(password);
		return 1;
	}
}

//ѡ��SOCK5 + ������֤
int socks5_auth_noauth(int fd)
{
	char answer[2] = { VERSION5, NOAUTH };
	writen(fd, (void *)answer, ARRAY_SIZE(answer));
	return 0;
}

//ѡ��SOCK5����£����������֧�ֵ�ǰ�汾�ŵĻ�Ӧ
void socks5_auth_notsupported(int fd)
{
	char answer[2] = { VERSION5, NOMETHOD };
	writen(fd, (void *)answer, ARRAY_SIZE(answer));
}

//ѡ��SOCK5����£�������֤
void socks5_auth(int fd, int methods_count)
{
	int supported = 0;
	int num = methods_count;
	for (int i = 0; i < num; i++) {
		char type;
		readn(fd, (void *)&type, 1);	//��ȡ��֤����
		log_message("Method AUTH %hhX", type);
		if (type == auth_type) {		//Ĭ�ϵ���������֤��auth_type = NOAUTH
			supported = 1;
		}
	}
	if (supported == 0) {
		//�����֧�֣��Ѱ汾�źʹ�����Ϣд��fd
		socks5_auth_notsupported(fd);
		//�ر�fd���ر�һ���߳�
		app_thread_exit(1, fd);
	}
	int ret = 0;
	switch (auth_type) {
	case NOAUTH:
		ret = socks5_auth_noauth(fd);
		break;
	case USERPASS:
		ret = socks5_auth_userpass(fd);
		break;
	}
	//��֤�ɹ�return�����ɹ��˳�
	if (ret == 0) {
		return;
	} else {
		app_thread_exit(1, fd);
	}
}

//ѡ��SOCK5����£���ȡָ��
int socks5_command(int fd)
{
	char command[4];
	readn(fd, (void *)command, ARRAY_SIZE(command));
	log_message("Command %hhX %hhX %hhX %hhX", command[0], command[1],
		    command[2], command[3]);
	return command[3];
}

//��ȡ�˿ں�
unsigned short int socks_read_port(int fd)
{
	unsigned short int p;
	readn(fd, (void *)&p, sizeof(p));
	log_message("Port %hu", ntohs(p));
	return p;
}

//��ȡip
char *socks_ip_read(int fd)
{
	char *ip = (char *)malloc(sizeof(char) * IPSIZE);
	readn(fd, (void *)ip, IPSIZE);
	log_message("IP %hhu.%hhu.%hhu.%hhu", ip[0], ip[1], ip[2], ip[3]);
	return ip;
}

//ѡ��SOCK5����£�����ip������Ӧ
void socks5_ip_send_response(int fd, char *ip, unsigned short int port)
{
	char response[4] = { VERSION5, OK, RESERVED, IP };
	writen(fd, (void *)response, ARRAY_SIZE(response));
	writen(fd, (void *)ip, IPSIZE);
	writen(fd, (void *)&port, sizeof(port));
}

//ѡ��SOCK5����£���ȡ����
char *socks5_domain_read(int fd, unsigned char *size)
{
	unsigned char s;
	readn(fd, (void *)&s, sizeof(s));
	char *address = (char *)malloc((sizeof(char) * s) + 1);
	readn(fd, (void *)address, (int)s);
	address[s] = 0;
	log_message("Address %s", address);
	*size = s;
	return address;
}

//����ip����
void socks5_domain_send_response(int fd, char *domain, unsigned char size,
				 unsigned short int port)
{
	char response[4] = { VERSION5, OK, RESERVED, DOMAIN };
	writen(fd, (void *)response, ARRAY_SIZE(response));
	writen(fd, (void *)&size, sizeof(size));
	writen(fd, (void *)domain, size * sizeof(char));
	writen(fd, (void *)&port, sizeof(port));
}

int socks4_is_4a(char *ip)
{
	return (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] != 0);
}

int socks4_read_nstring(int fd, char *buf, int size)
{
	char sym = 0;
	int nread = 0;
	int i = 0;

	while (i < size) {
		nread = recv(fd, &sym, sizeof(char), 0);

		if (nread <= 0) {
			break;
		} else {
			buf[i] = sym;
			i++;
		}

		if (sym == 0) {
			break;
		}
	}

	return i;
}

void socks4_send_response(int fd, int status)
{
	char resp[8] = {0x00, (char)status, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	writen(fd, (void *)resp, ARRAY_SIZE(resp));
}

void app_socket_pipe(int fd0, int fd1)
{
	int maxfd, ret;
	fd_set rd_set;
	size_t nread;
	char buffer_r[BUFSIZE];

    log_message("Connecting two sockets");

	maxfd = (fd0 > fd1) ? fd0 : fd1;
	while (1) {
		FD_ZERO(&rd_set);
		FD_SET(fd0, &rd_set);
		FD_SET(fd1, &rd_set);
		ret = select(maxfd + 1, &rd_set, NULL, NULL, NULL);

		if (ret < 0 && errno == EINTR) {
			continue;
		}

		if (FD_ISSET(fd0, &rd_set)) {
			nread = recv(fd0, buffer_r, BUFSIZE, 0);
			if (nread <= 0)
				break;
			send(fd1, (const void *)buffer_r, nread, 0);
		}

		if (FD_ISSET(fd1, &rd_set)) {
			nread = recv(fd1, buffer_r, BUFSIZE, 0);
			if (nread <= 0)
				break;
			send(fd0, (const void *)buffer_r, nread, 0);
		}
	}
}

//app_loop��ÿ���������̴߳Ӵ˿�ʼִ��
void *app_thread_process(void *fd)
{
	int net_fd = *(int *)fd;
	int version = 0;
	int inet_fd = -1;

	//��net_fd�ж�ȡѡ��İ汾
	//һ������ѡ��SOCK5
	//���������п���ѡ��SOCK4
	char methods = socks_invitation(net_fd, &version);

	switch (version) {
	case VERSION5: {
			socks5_auth(net_fd, methods);			//��֤
			int command = socks5_command(net_fd);	//���׽����ж�ȡ����

			if (command == IP) {								//ʶ��Ϊip
				char *ip = socks_ip_read(net_fd);				//��ȡip��ַ
				unsigned short int p = socks_read_port(net_fd);	//��ȡ�˿ں�

				inet_fd = app_connect(IP, (void *)ip, ntohs(p));	//����ip�������ӣ�����ֵ����app_connect�д��������׽���
				if (inet_fd == -1) {
					app_thread_exit(1, net_fd);
				}
				socks5_ip_send_response(net_fd, ip, p);				//���ݵ�ǰ�����е��׽��֡�ip���˿ڻ�û�Ӧ
				free(ip);
				break;
				//�������ִ���ͬ�ϣ���֮ͬ������Ҫ�Ƚ�������
			} else if (command == DOMAIN) {
				unsigned char size;
				char *address = socks5_domain_read(net_fd, &size);
				unsigned short int p = socks_read_port(net_fd);

				inet_fd = app_connect(DOMAIN, (void *)address, ntohs(p));
				if (inet_fd == -1) {
					app_thread_exit(1, net_fd);
				}
				socks5_domain_send_response(net_fd, address, size, p);
				free(address);
				break;
			} else {
				app_thread_exit(1, net_fd);
			}
		}
		case VERSION4: {
			if (methods == 1) {
				char ident[255];
				unsigned short int p = socks_read_port(net_fd);
				char *ip = socks_ip_read(net_fd);
				socks4_read_nstring(net_fd, ident, sizeof(ident));

				if (socks4_is_4a(ip)) {
					char domain[255];
					socks4_read_nstring(net_fd, domain, sizeof(domain));
					log_message("Socks4A: ident:%s; domain:%s;", ident, domain);
					inet_fd = app_connect(DOMAIN, (void *)domain, ntohs(p));
				} else {
					log_message("Socks4: connect by ip & port");
					inet_fd = app_connect(IP, (void *)ip, ntohs(p));
				}

				if (inet_fd != -1) {
					socks4_send_response(net_fd, 0x5a);
				} else {
					socks4_send_response(net_fd, 0x5b);
					free(ip);
					app_thread_exit(1, net_fd);
				}

				free(ip);
            } else {
                log_message("Unsupported mode");
            }
			break;
		}
	}

	app_socket_pipe(inet_fd, net_fd);
	close(inet_fd);
	app_thread_exit(0, net_fd);

    return NULL;
}

int app_loop()
{
	int sock_fd, net_fd;
	int optval = 1;

	//sockaddr_in������������ͨ�ŵĵ�ַ��ͬ���͵Ļ���sockaddr
	//�����ĸ�������sin_family		��ַ��
	//			  sin_port      16λTCP/UDP�˿ں�
	//			  sin_addr      32λip��ַ�������һ���ṹ�壬�ڲ�����һ��s_addr����ʾ32λipv4��ַ��
	//            sin_zero[8]   ��ʹ��
	//һ�㶼����sockaddr_in������͸�ֵsocket
	//sockaddr������������
	struct sockaddr_in local, remote;
	
	//�洢Զ�˵ĵ�ַ���ȣ���socklen_t��Ϊ����accept�ĵ���������
	socklen_t remotelen;

	//socket����ԭ�ͣ�socket(int domain, int type, int protocol)
	//����һ��Э����Ϊdomain��Э������Ϊtype��Э����Ϊprotocol���׽����ļ�������
	//AF_INET��ipv4Э��
	//SOCK_STREAM��TCP����
	//���һ��Э��ֻ��һ���ض����ͣ���ô����������Ϊ0

	//socket(AF_INET, SOCK_STREAM, 0) ���Ǵ�����ʽ�׽���
	//���ʧ�ܻ᷵��-1��Ȼ����ʾsocket()��Ȼ���˳�����
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		log_message("socket()");
		exit(1);
	}

	//setsockopt���ڶ��׽��ֽ�������
	//������������closesocket��������ø�socket
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0) {
		log_message("setsockopt()");
		exit(1);
	}

	//��ʼ��local
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;

	//htonl			������һ��32λ���������ֽ�˳��ת��Ϊ�����ֽ�˳��
	//INADDR_ANY	ָ����ַΪ0.0.0.0�ĵ�ַ����ʾ��ȷ���ĵ�ַ�������е�ַ�����������ַ��
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	//htons			������htonl���������ֽ�˳��תΪ�����ֽ�˳��
	//��htonl�Ĳ�ͬ���ڣ�htonl()--"Host to Network Long"
	//				   htons()--"Host to Network Short"
	local.sin_port = htons(port);

	//bind() ���׽ӿڷ���һ������������Ϊ�׽ӿڽ����������󣬼���һ���ص�ַ��һ�׽ӿڰ�
	if (bind(sock_fd, (struct sockaddr *)&local, sizeof(local)) < 0) 
	{
		log_message("bind()");
		exit(1);
	}

	//listen()	����һ���׽ӿڲ��������������
	//�ڶ��������ǵȴ����Ӷ��е���󳤶�
	if (listen(sock_fd, 25) < 0) 
	{
		log_message("listen()");
		exit(1);
	}


	remotelen = sizeof(remote);
	memset(&remote, 0, sizeof(remote));

	log_message("Listening port %d...", port);

	//pthread_t ���������߳�ID
	pthread_t worker;
	while (1) {
		//����ͻ������������󣬱���ʹ��accpet�����ܿͻ��˵�����
		//��һ�����������˷����ip��˿���Ϣ
		//�ڶ�������addr���ڴ�ſͻ��˵ĵ�ַ
		//�����������ڵ��ú���ʱ�ᱻ����Ϊaddrָ������ĳ��ȣ��ڵ��ý���������Ϊʵ�ʵ�ַ��Ϣ�ĳ���
		//�������������ȴ�ֱ���пͻ������󵽴�
		//����ֵ��һ���µ��׽���������������Ϳͻ����µ����ӣ����԰������Ϊһ���ͻ��˵�socket�����socket�������ǿͻ��˵�ip��port
		//����µ��׽���Ҳ���sock_fd�м̳з�������ip��port��Ϣ
		if ((net_fd =
		     accept(sock_fd, (struct sockaddr *)&remote,
			    &remotelen)) < 0) {
			log_message("accept()");
			exit(1);
		}
        int one = 1;

		//���÷�����socket
		//�ڶ�������ָ��ѡ���������ͣ������SOL_SOCKET�ǻ����׽ӿڣ��������TCP�׽ӿ�
		//������������ѡ�����ƣ������TCP_NODELAY�ǲ�ʹ��Nagle�㷨
		//���ĸ�������һ��ָ�������ָ�� ���Ϳ��������͡��׽ӿ�
		//���һ��������ѡ��ֵ�Ĵ�С
        setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &one, sizeof(one));

		//pthread_create��linux�Ȳ���ϵͳ�����̵߳ĺ����������Ǵ����߳�
		//�ɹ�����0��������-1
		//��һ���������µ��߳�IDָ����ڴ浥Ԫ
		//�ڶ����������߳����ԣ�Ĭ��ΪNULL
		//������������һ������ָ�룬���´������̴߳���������ĵ�ַ��ʼִ��
		//���ĸ������ǲ�����Ĭ��ΪNULL���������������Ҫ�������ͰѲ�������ṹ�в��ѵ�ַ��Ϊ��������
		//�����ǰ�net_fd��Ϊ��������app_thread_process
		//net_fd�������´������׽���
		if (pthread_create
		    (&worker, NULL, &app_thread_process,
		     (void *)&net_fd) == 0) {
			//pthread_detach������Ϊһ���̱߳�ʶ������������̴߳����߳��з�����������߳̽�������Դ�Զ�����
			pthread_detach(worker);
		} else {
			log_message("pthread_create()");
		}
	}
}

void daemonize()
{
	pid_t pid;		//pid_t �ǽ��̺�����
	int x;

	pid = fork();	//�ѵ�ǰ���еĳ����Ϊ������ȫһ���Ľ��̣�ÿ�����̶�����һ���Ӵ����ͬһλ�ÿ�ʼִ�еĽ���
					//����Ҫ����������һ��int
					//����ɹ���������������ֵ���ӽ��̷���0�������̷����ӽ���pid��������-1

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	//setsid���ӽ��̲����ն�Ӱ�죬�ն��˳�����Ӱ���ӽ���
	if (setsid() < 0) {
		exit(EXIT_FAILURE);
	}

	//SIGCHLD �ӽ�����ֹ��ֹͣʱ���Ѵ��źŷ��͸�������
	//SIGHUP  �Ҷ��źţ��ڿ����ն˻���ƽ�������ʱ����
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	//umask�����û��ڴ����ļ�ʱ��Ĭ��Ȩ��
	//umask(0)�Ǹ������Ȩ�ޣ���777
	umask(0);
	chdir("/");

	//sysconf�������鿴CPU�������Ϣ
	//_SC_OPEN_MAX��ÿ����������ʱ�Ĵ򿪵��ļ���Ŀ
	for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
		close(x);
	}

	/*�ػ����̲�����Ҫ���������⣺
	1.ΪʲôҪfork����
		�ٽ�������׽��̲��ܵ���setsid�����д������ǵ�һ��fork��ԭ��ִ�е�һ��fork�ø������˳����ӽ����˳�����ʱ��
		  �ӽ�����Ϊ�̳��˸����̵Ľ�����GID�Լ��Լ�����һ��pid��gid��pid�������ӽ��̲����ܳ�Ϊ��������׽��̣��Ϳ���ִ��setsid��
		�ڵ���sid������֮ǰ�Ŀ����ն˵����ӻ�Ͽ�����ִ��һ��fork�����ӽ����˳�������̼���������̲����Ϊ����
		  ��������׽��̣���ʹ�������ܴ򿪿����նˣ������ػ����̾͵õ���һ���ɾ��Ļ��������ᱻ�ն˲������źŸ���
		���������ڶ���fork��Ŀ�ľ��Ƿ�ֹ�����ٴ�һ�������ն�
	2.chdir������
		�������ӽ��̻�����̿��ܲ���ԭĿ¼�����������޸�һ�¹���Ŀ¼*/

}

void usage(char *app)
{
	printf
	    ("USAGE: %s [-h][-n PORT][-a AUTHTYPE][-u USERNAME][-p PASSWORD][-l LOGFILE]\n",
	     app);
	printf("AUTHTYPE: 0 for NOAUTH, 2 for USERPASS\n");
	printf
	    ("By default: port is 1080, authtype is no auth, logfile is stdout\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int ret;
	log_file = stdout;					//����־��ӡ����Ļ
	auth_type = NOAUTH;					//Ĭ��������֤
	arg_username = "user";				//�û���
	arg_password = "pass";				//����
	pthread_mutex_init(&lock, NULL);	//�������߳���
										//ʹ�û������֮ǰҪ�ȳ�ʼ��
										//��һ��������pthread_mutex_t���͵�ָ��

	signal(SIGPIPE, SIG_IGN);			//signal��������⵽��һ�����������źžͻ�ִ�еڶ�������
										//�ڶ���������һ������ָ��
										//SIG_IGN��ʾ�����ź�
										//����һ���Զ��Ѿ��رյ�socket��������write���ڶ��ξͻ����SIGPIPE������ź�Ĭ�Ͻ�������
										//Ϊ�˱�������˳������Բ���SIGPIPE�źţ�Ȼ������SIG_IGN������

	//getoptѡ�����������������ѡ���ַ���
	//ѡ���ַ����У����ѡ�ͺ����ð�ţ�˵�����ѡ����������
	//���������ð�ţ�˵��������ѡ
	while ((ret = getopt(argc, argv, "n:u:p:l:a:hd")) != -1) 
	{
		switch (ret) 
		{
			case 'd':
			{
				daemon_mode = 1;	//�����ػ�ģʽ
				daemonize();		//�����ػ�����
				break;
			}
			case 'n':
			{
				port = atoi(optarg) & 0xffff;	//optargָ��ǰѡ��Ĳ�����ָ��
												//�˿ں�1080(0100 0011 1000)��0xfff�����������ת��Ϊ������
				break;
			}
			case 'u':
			{
				arg_username = strdup(optarg);
				break;
			}
			case 'p':
			{
				arg_password = strdup(optarg);
				break;
			}
			case 'l':
			{
				freopen(optarg, "wa", log_file);
				break;
			}
			case 'a':
			{
				auth_type = atoi(optarg);
				break;
			}
			case 'h':
			default:
				usage(argv[0]);				//��ʾ��������ʾ
		}
	}
	log_message("Starting with authtype %X", auth_type);	//��ʾ��֤����
	if (auth_type != NOAUTH)								//����֤�������
	{
		log_message("Username is %s, password is %s", arg_username,
			    arg_password);
	}
	app_loop();												//����ѭ��
															//app_loop����Ҫ�����ǽ��������뽨���߳�
	return 0;
}

