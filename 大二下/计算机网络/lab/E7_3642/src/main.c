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
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))	//用于获取当前数组长度
#define ARRAY_INIT    {0}

unsigned short int port = 1080;						//默认端口1080
int daemon_mode = 0;								//是否需要守护进程
int auth_type;										//认证类型（默认为无需认证）
char *arg_username;									//用户名（选择用户名+密码认证情况下有用）
char *arg_password;									//密码（选择用户名+密码认证情况下有用）
FILE *log_file;										//日志文件的输出，默认为stdout
pthread_mutex_t lock;							//互斥变量的数据类型，用于线程锁，类似于java的reentrantlock

enum socks					//使用什么版本的socket
{
	RESERVED = 0x00,
	VERSION4 = 0x04,
	VERSION5 = 0x05
};

enum socks_auth_methods		//认证类型
{
	NOAUTH = 0x00,			//无需认证
	USERPASS = 0x02,		//用户名+密码
	NOMETHOD = 0xff
};

enum socks_auth_userpass	//用户名+密码认证状态
{
	AUTH_OK = 0x00,
	AUTH_VERSION = 0x01,
	AUTH_FAIL = 0xff
};

enum socks_command			//指令
{
	CONNECT = 0x01
};

enum socks_command_type		//指令类型
{
	IP = 0x01,
	DOMAIN = 0x03
};

enum socks_status			//套接字状态
{
	OK = 0x00,
	FAILED = 0x05
};

//形参个数与类型不确定，通知编译器在函数调用时不检查形参类型和实参类型是否相同，也不检查参数个数
void log_message(const char *message, ...)
{
	if (daemon_mode)	//如果是守护进程模式，直接退出本函数
	{
		return;
	}

	char vbuffer[255];			//v开头的一般是可变的变量
	va_list args;				//typedef char* va_list
	va_start(args, message);	//va_start 用于初始化va_list类型的变量，第二个参数是最后一个传递给函数的已知的固定参数，即省略号之前的参数

	//ARRAY_SIZE好用，可以记住
	vsnprintf(vbuffer, ARRAY_SIZE(vbuffer), message, args);		//把args按照messgae的形式写入vbuffer
	va_end(args);

	//准备打印时间
	time_t now;
	time(&now);
	char *date = ctime(&now);
	date[strlen(date) - 1] = '\0';

	pthread_t self = pthread_self();	//获取当前线程自身pid

	//errno用于记录系统最后一次错误代码
	if (errno != 0) {
		pthread_mutex_lock(&lock);
		//error用于把错误代码转换为对应的可读错误
		fprintf(log_file, "[%s][%lu] Critical: %s - %s\n", date, self,
			vbuffer, strerror(errno));
		errno = 0;
		pthread_mutex_unlock(&lock);
	} else {
		fprintf(log_file, "[%s][%lu] Info: %s\n", date, self, vbuffer);
	}
	//把输出缓冲区中的东西打印到stdout上
	fflush(log_file);
}

//用来读取消息的函数
int readn(int fd, void *buf, int n)
{
	int nread, left = n;
	while (left > 0) {
		//read(int fd, void *buf, size_t count)
		//把fd所指的文件传送count个字节到buf所指的内存中
		//返回回值为实际读取到的字节数, 如果返回0, 表示已到达文件尾或是无可读取的数据
		//若参数count 为0, 则read()不会有作用并返回0
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

//用来写消息的函数
int writen(int fd, void *buf, int n)
{
	int nwrite, left = n;
	while (left > 0) {
		//write(int fd, const void * buf, size_t count)
		//把参数buf所指的内存写入count个字节到参数放到所指的文件内
		//如果顺利write()会返回实际写入的字节数。当有错误发生时则返回-1，错误代码存入errno中
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

//用于关闭socket和线程的函数
void app_thread_exit(int ret, int fd)
{
	//关闭fd文件
	//退出ret所指线程
	close(fd);
	pthread_exit((void *)&ret);
}

//主要连接函数
int app_connect(int type, void *buf, unsigned short int portnum)
{
	int fd;
	struct sockaddr_in remote;
	char address[16];

	memset(address, 0, ARRAY_SIZE(address));

	if (type == IP)		//根据ip进行连接
	{
		char *ip = (char *)buf;
		snprintf(address, ARRAY_SIZE(address), "%hhu.%hhu.%hhu.%hhu",
			 ip[0], ip[1], ip[2], ip[3]);
		memset(&remote, 0, sizeof(remote));
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = inet_addr(address);
		remote.sin_port = htons(portnum);

		fd = socket(AF_INET, SOCK_STREAM, 0);		//创建流式套接字

		//connect(SOCKET s, const struct sockaddr * name, int namelen)
		//建立与指定socket的连接
		//name是要连接的套接字的指针
		//namelen是sockaddr结构体的长度
		if (connect(fd, (struct sockaddr *)&remote, sizeof(remote)) < 0)	//如果连接失败
		{
			log_message("connect() in app_connect");
			close(fd);
			return -1;
		}

		return fd;
		//domain主要作用同ip部分，不同地方在于要先解析域名
	} else if (type == DOMAIN) {
		char portaddr[6];
		struct addrinfo *res;
		snprintf(portaddr, ARRAY_SIZE(portaddr), "%d", portnum);
		log_message("getaddrinfo: %s %s", (char *)buf, portaddr);
		//关键代码：getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result)
		//处理名字到地址以及服务到端口这两种转换
		//hostname：主机名/地址串（如ipv4的点分十进制、ipv6的16进制串）
		//service：要么是端口号，要么是已有的服务名称，比如http、ftp
		//hints：空指针，或者是某个指向addrinfo的指针
		//result：本函数通过result指针参数返回一个指向addrinfo结构体链表的指针
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

//读取版本号
int socks_invitation(int fd, int *version)
{
	char init[2];

	//把fd所指的文件传送到init字符数组中去
	int nread = readn(fd, (void *)init, ARRAY_SIZE(init));
	if (nread == 2 && init[0] != VERSION5 && init[0] != VERSION4) {
        log_message("They send us %hhX %hhX", init[0], init[1]);
		log_message("Incompatible version!");
		app_thread_exit(0, fd);
	}
	log_message("Initial %hhX %hhX", init[0], init[1]);
	//获得版本号
	*version = init[0];
	//根据实际运行结果，init[1]应该是连接数/线程数
	return init[1];
}

//选择SOCK5情况下，获取用户名
char *socks5_auth_get_user(int fd)
{
	unsigned char size;
	readn(fd, (void *)&size, sizeof(size));

	char *user = (char *)malloc(sizeof(char) * size + 1);
	readn(fd, (void *)user, (int)size);
	user[size] = 0;

	return user;
}

//选择SOCK5情况下，获取密码
char *socks5_auth_get_pass(int fd)
{
	unsigned char size;
	readn(fd, (void *)&size, sizeof(size));

	char *pass = (char *)malloc(sizeof(char) * size + 1);
	readn(fd, (void *)pass, (int)size);
	pass[size] = 0;

	return pass;
}

//选择SOCK5 + 用户密码认证
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

//选择SOCK5 + 无需认证
int socks5_auth_noauth(int fd)
{
	char answer[2] = { VERSION5, NOAUTH };
	writen(fd, (void *)answer, ARRAY_SIZE(answer));
	return 0;
}

//选择SOCK5情况下，做出如果不支持当前版本号的回应
void socks5_auth_notsupported(int fd)
{
	char answer[2] = { VERSION5, NOMETHOD };
	writen(fd, (void *)answer, ARRAY_SIZE(answer));
}

//选择SOCK5情况下，进行认证
void socks5_auth(int fd, int methods_count)
{
	int supported = 0;
	int num = methods_count;
	for (int i = 0; i < num; i++) {
		char type;
		readn(fd, (void *)&type, 1);	//读取认证类型
		log_message("Method AUTH %hhX", type);
		if (type == auth_type) {		//默认的是无需认证，auth_type = NOAUTH
			supported = 1;
		}
	}
	if (supported == 0) {
		//如果不支持，把版本号和错误消息写入fd
		socks5_auth_notsupported(fd);
		//关闭fd，关闭一个线程
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
	//认证成功return，不成功退出
	if (ret == 0) {
		return;
	} else {
		app_thread_exit(1, fd);
	}
}

//选择SOCK5情况下，读取指令
int socks5_command(int fd)
{
	char command[4];
	readn(fd, (void *)command, ARRAY_SIZE(command));
	log_message("Command %hhX %hhX %hhX %hhX", command[0], command[1],
		    command[2], command[3]);
	return command[3];
}

//读取端口号
unsigned short int socks_read_port(int fd)
{
	unsigned short int p;
	readn(fd, (void *)&p, sizeof(p));
	log_message("Port %hu", ntohs(p));
	return p;
}

//读取ip
char *socks_ip_read(int fd)
{
	char *ip = (char *)malloc(sizeof(char) * IPSIZE);
	readn(fd, (void *)ip, IPSIZE);
	log_message("IP %hhu.%hhu.%hhu.%hhu", ip[0], ip[1], ip[2], ip[3]);
	return ip;
}

//选择SOCK5情况下，根据ip做出回应
void socks5_ip_send_response(int fd, char *ip, unsigned short int port)
{
	char response[4] = { VERSION5, OK, RESERVED, IP };
	writen(fd, (void *)response, ARRAY_SIZE(response));
	writen(fd, (void *)ip, IPSIZE);
	writen(fd, (void *)&port, sizeof(port));
}

//选择SOCK5情况下，读取域名
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

//类似ip部分
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

//app_loop中每个创建的线程从此开始执行
void *app_thread_process(void *fd)
{
	int net_fd = *(int *)fd;
	int version = 0;
	int inet_fd = -1;

	//从net_fd中读取选择的版本
	//一般我们选用SOCK5
	//火狐浏览器中可以选择SOCK4
	char methods = socks_invitation(net_fd, &version);

	switch (version) {
	case VERSION5: {
			socks5_auth(net_fd, methods);			//认证
			int command = socks5_command(net_fd);	//从套接字中读取命令

			if (command == IP) {								//识别为ip
				char *ip = socks_ip_read(net_fd);				//读取ip地址
				unsigned short int p = socks_read_port(net_fd);	//读取端口号

				inet_fd = app_connect(IP, (void *)ip, ntohs(p));	//根据ip建立连接，返回值是在app_connect中创建的新套接字
				if (inet_fd == -1) {
					app_thread_exit(1, net_fd);
				}
				socks5_ip_send_response(net_fd, ip, p);				//根据当前进程中的套接字、ip、端口获得回应
				free(ip);
				break;
				//域名部分大致同上，不同之处在于要先解析域名
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

	//sockaddr_in用来处理网络通信的地址，同类型的还有sockaddr
	//含有四个变量：sin_family		地址族
	//			  sin_port      16位TCP/UDP端口号
	//			  sin_addr      32位ip地址（这个是一个结构体，内部还有一个s_addr，表示32位ipv4地址）
	//            sin_zero[8]   不使用
	//一般都是用sockaddr_in来定义和赋值socket
	//sockaddr用来函数传参
	struct sockaddr_in local, remote;
	
	//存储远端的地址长度，用socklen_t是为了做accept的第三个参数
	socklen_t remotelen;

	//socket函数原型：socket(int domain, int type, int protocol)
	//创建一个协议族为domain、协议类型为type、协议编号为protocol的套接字文件描述符
	//AF_INET是ipv4协议
	//SOCK_STREAM是TCP连接
	//如果一个协议只有一种特定类型，那么第三个参数为0

	//socket(AF_INET, SOCK_STREAM, 0) 这是创建流式套接字
	//如果失败会返回-1，然后提示socket()，然后退出程序
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		log_message("socket()");
		exit(1);
	}

	//setsockopt用于对套接字进行设置
	//这里是设置在closesocket后继续重用该socket
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0) {
		log_message("setsockopt()");
		exit(1);
	}

	//初始化local
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;

	//htonl			用来把一个32位数从主机字节顺序转换为网络字节顺序
	//INADDR_ANY	指定地址为0.0.0.0的地址，表示不确定的地址，或“所有地址”、“任意地址”
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	//htons			类似于htonl，将主机字节顺序转为网络字节顺序
	//与htonl的不同在于：htonl()--"Host to Network Long"
	//				   htons()--"Host to Network Short"
	local.sin_port = htons(port);

	//bind() 给套接口分配一个本地名字来为套接口建立本地捆绑，即将一本地地址与一套接口绑定
	if (bind(sock_fd, (struct sockaddr *)&local, sizeof(local)) < 0) 
	{
		log_message("bind()");
		exit(1);
	}

	//listen()	创建一个套接口并监听申请的连接
	//第二个参数是等待连接队列的最大长度
	if (listen(sock_fd, 25) < 0) 
	{
		log_message("listen()");
		exit(1);
	}


	remotelen = sizeof(remote);
	memset(&remote, 0, sizeof(remote));

	log_message("Listening port %d...", port);

	//pthread_t 用于声明线程ID
	pthread_t worker;
	while (1) {
		//如果客户端有连接请求，必须使用accpet来接受客户端的请求
		//第一个参数包含了服务的ip与端口信息
		//第二个参数addr用于存放客户端的地址
		//第三个参数在调用函数时会被设置为addr指向区域的长度，在调用结束后被设置为实际地址信息的长度
		//本函数会阻塞等待直到有客户端请求到达
		//返回值是一个新的套接字描述符，代表和客户端新的连接，可以把它理解为一个客户端的socket，这个socket包含的是客户端的ip和port
		//这个新的套接字也会从sock_fd中继承服务器的ip和port信息
		if ((net_fd =
		     accept(sock_fd, (struct sockaddr *)&remote,
			    &remotelen)) < 0) {
			log_message("accept()");
			exit(1);
		}
        int one = 1;

		//设置服务器socket
		//第二个参数指定选项代码的类型，上面的SOL_SOCKET是基本套接口，这里的是TCP套接口
		//第三个参数是选项名称，这里的TCP_NODELAY是不使用Nagle算法
		//第四个参数是一个指向变量的指针 类型可以是整型、套接口
		//最后一个参数是选项值的大小
        setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &one, sizeof(one));

		//pthread_create是linux等操作系统创建线程的函数，功能是创建线程
		//成功返回0，出错返回-1
		//第一个参数是新的线程ID指向的内存单元
		//第二个参数是线程属性，默认为NULL
		//第三个参数是一个函数指针，让新创建的线程从这个函数的地址开始执行
		//第四个参数是参数，默认为NULL，如果上述函数需要参数，就把参数放入结构中并把地址作为参数传入
		//这里是把net_fd作为参数传入app_thread_process
		//net_fd是上面新创建的套接字
		if (pthread_create
		    (&worker, NULL, &app_thread_process,
		     (void *)&net_fd) == 0) {
			//pthread_detach，参数为一个线程标识符，把这个子线程从主线程中分离出来，子线程结束后，资源自动回收
			pthread_detach(worker);
		} else {
			log_message("pthread_create()");
		}
	}
}

void daemonize()
{
	pid_t pid;		//pid_t 是进程号类型
	int x;

	pid = fork();	//把当前运行的程序分为两个完全一样的进程，每个进程都启动一个从代码的同一位置开始执行的进程
					//不需要参数并返回一个int
					//如果成功，返回两次两个值，子进程返回0，父进程返回子进程pid；出错返回-1

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	//setsid后，子进程不受终端影响，终端退出，不影响子进程
	if (setsid() < 0) {
		exit(EXIT_FAILURE);
	}

	//SIGCHLD 子进程终止或停止时，把此信号发送给父进程
	//SIGHUP  挂断信号，在控制终端或控制进程死亡时发出
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	//umask设置用户在创建文件时的默认权限
	//umask(0)是给予最大权限，即777
	umask(0);
	chdir("/");

	//sysconf是用来查看CPU的相关信息
	//_SC_OPEN_MAX是每个进程运行时的打开的文件数目
	for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
		close(x);
	}

	/*守护进程部分主要有两个问题：
	1.为什么要fork两次
		①进程组的首进程不能调用setsid，会有错误，这是第一个fork的原因，执行第一个fork让父进程退出，子进程退出，这时候
		  子进程因为继承了父进程的进程组GID以及自己还有一个pid，gid≠pid，所以子进程不可能成为进程组的首进程，就可以执行setsid了
		②调用sid后所有之前的控制终端的连接会断开，再执行一次fork，让子进程退出，孙进程继续，孙进程不会成为所在
		  进程组的首进程，就使得它不能打开控制终端，这样守护进程就得到了一个干净的环境，不会被终端产生的信号干扰
		简单来讲，第二次fork的目的就是防止进程再打开一个控制终端
	2.chdir的作用
		产生的子进程或孙进程可能不在原目录工作，所以修改一下工作目录*/

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
	log_file = stdout;					//把日志打印到屏幕
	auth_type = NOAUTH;					//默认无需认证
	arg_username = "user";				//用户名
	arg_password = "pass";				//密码
	pthread_mutex_init(&lock, NULL);	//作用是线程锁
										//使用互斥变量之前要先初始化
										//第一个参数是pthread_mutex_t类型的指针

	signal(SIGPIPE, SIG_IGN);			//signal函数，检测到第一个（参数）信号就会执行第二个参数
										//第二个参数是一个函数指针
										//SIG_IGN表示忽视信号
										//当对一个对端已经关闭的socket调用两次write，第二次就会产生SIGPIPE，这个信号默认结束进程
										//为了避免进程退出，可以捕获SIGPIPE信号，然后设置SIG_IGN忽视它

	//getopt选项函数，第三个参数是选项字符串
	//选项字符串中，如果选型后面带冒号，说明这个选项必须带参数
	//如果是两个冒号，说明参数可选
	while ((ret = getopt(argc, argv, "n:u:p:l:a:hd")) != -1) 
	{
		switch (ret) 
		{
			case 'd':
			{
				daemon_mode = 1;	//设置守护模式
				daemonize();		//进入守护进程
				break;
			}
			case 'n':
			{
				port = atoi(optarg) & 0xffff;	//optarg指向当前选项的参数的指针
												//端口号1080(0100 0011 1000)和0xfff进行与操作，转换为二进制
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
				usage(argv[0]);				//显示帮助、提示
		}
	}
	log_message("Starting with authtype %X", auth_type);	//提示认证类型
	if (auth_type != NOAUTH)								//有认证的情况下
	{
		log_message("Username is %s, password is %s", arg_username,
			    arg_password);
	}
	app_loop();												//进入循环
															//app_loop的主要作用是建立连接与建立线程
	return 0;
}

