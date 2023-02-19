#define HAVE_REMOTE
#define WIN32
#define WPCAP
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "ws2_32.lib")

#include <pcap.h>
#include <packet32.h>
#include <ntddndis.h>
#include <stdio.h>


/* 4�ֽڵ�IP��ַ */
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

typedef struct ip_header {
	u_char ver_ihl; // Version (4 bits) +Internet header length(4 bits)
	u_char tos; // Type of service
	u_short tlen; // Total length
	u_short identification; // Identification
	u_short flags_fo; // Flags (3 bits) + Fragmentoffset(13 bits)
	u_char ttl; // Time to live
	u_char proto; // Protocol
	u_short crc; // Header checksum
	u_char saddr[4]; // Source address
	u_char daddr[4]; // Destination address
	u_int op_pad; // Option + Padding
} ip_header;

typedef struct mac_header {
	u_char dest_addr[6];
	u_char src_addr[6];
	u_char type[2];
} mac_header;

/* UDP �ײ�*/
typedef struct udp_header {
	u_short sport;          // Դ�˿�(Source port)
	u_short dport;          // Ŀ�Ķ˿�(Destination port)
	u_short len;            // UDP���ݰ�����(Datagram length)
	u_short crc;            // У���(Checksum)
}udp_header;

/* �ص�����ԭ�� */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);
int count = 0;
struct timeval old_ts = { 0,0 };
time_t timep;
struct tm* p;
time_t oldtime;
int all_len = 0;
int old_time;


main()
{
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[] = "ip and udp";
	struct bpf_program fcode;

	/* ����豸�б� */
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	//findalldevs_ex(char *source, struct pcap_rmtauth *auth, pcap_if_t **alldevs, char *errbuf  )
	//source �����ǡ�rpcap://������ʾ������������#define PCAP_SRC_IF_STRING ��rpcap://�� 
	//auth:ָ��pcap_rmtauth�ṹ��ָ�룬�����������ӵ�Զ����������Ȩ��Ϣ���ڲ�ѯ���ػ���ʱ���˲���ûʲô���壬����ΪNULL��
	//alldevs: ָ��pcap_if_t�ṹ��ָ�룬�˺�������ʱ����ָ�뱻����Ϊ����õ��豸�ӿ��б�ĵ�һ��Ԫ�أ��б��ÿһ��Ԫ�ض���Pcap_if_t�ṹ��
	//����ֵ���ɹ�����0��alldevs�����豸�б�alldevs����ΪNULL�����򷵻أ�1���Ǿ���˵ϵͳû���κνӿڿ����оٵġ��������Ϣ��errbuf���淵��

	/* ��ӡ�б� */
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &inum);

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* ��ת����ѡ�豸 */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* �������� */
	if ((adhandle = pcap_open(d->name,  // �豸��
		65536,     // Ҫ��׽�����ݰ��Ĳ��� 
				   // 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
		PCAP_OPENFLAG_PROMISCUOUS,         // ����ģʽ
		1000,      // ��ȡ��ʱʱ��
		NULL,      // Զ�̻�����֤
		errbuf     // ���󻺳��
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* ���������·�㣬Ϊ�˼򵥣�����ֻ������̫�� */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	if (d->addresses != NULL)
		/* ��ýӿڵ�һ����ַ������ */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* ����ӿ�û�е�ַ����ô���Ǽ���һ��C������� */
		netmask = 0xffffff;


	//���������
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	//���ù�����
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}


	time(&timep);
	p = localtime(&timep); //�˺�����õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ�� 
	oldtime = timep;
	old_time = time(&oldtime);

	printf("\nlistening on %s...\n", d->description);

	/* �ͷ��豸�б� */
	pcap_freealldevs(alldevs);

	/* ��ʼ��׽ */
	pcap_loop(adhandle, 0, packet_handler, NULL);

	return 0;
}

/* �ص����������յ�ÿһ�����ݰ�ʱ�ᱻlibpcap������ */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	struct tm* ltime;
	char timestr[16];
	mac_header* mh;
	ip_header* ih;
	time_t local_tv_sec;

	FILE* fp = fopen("Listen_MAC_IP.csv", "a+");

	time(&timep);
	p = localtime(&timep); //�˺�����õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ��
	printf("%d-%d-%d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);


	/* ��ʱ���ת���ɿ�ʶ��ĸ�ʽ */
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
	printf("%s  ", timestr);

	/* ��ӡ���ݰ��ĳ��� */
	printf("len:%d\n ", header->len);

	int length = sizeof(mac_header) + sizeof(ip_header);

	mh = (mac_header*)pkt_data;
	ih = (ip_header*)(pkt_data + sizeof(mac_header)); //length of ethernet header


	printf("  ");
	//printf("\tsrc_addr: ");
	for (int i = 0; i < 6; i++) 
	{
		printf("%02X ", mh->src_addr[i]);
	}

	printf("  ");
	for (int i = 0; i < 4; i++) {
		printf("%d.", ih->saddr[i]);
	}

	for (int i = 0; i < 6; i++) {
		printf("%02X ", mh->dest_addr[i]);
	}

	printf("  ");
	for (int i = 0; i < 4; i++) {
		printf("%d.", ih->daddr[i]);
	}

	fprintf(fp, "%s,", timestr);

	fprintf(fp, "%02X-%02X-%02X-%02X-%02X-%02X,",
		mh->src_addr[0],
		mh->src_addr[1],
		mh->src_addr[2],
		mh->src_addr[3],
		mh->src_addr[4],
		mh->src_addr[5]);

	fprintf(fp, "%d.%d.%d.%d,",
		ih->saddr[0],
		ih->saddr[1],
		ih->saddr[2],
		ih->saddr[3]);

	fprintf(fp, "%02X-%02X-%02X-%02X-%02X-%02X,",
		mh->dest_addr[0],
		mh->dest_addr[1],
		mh->dest_addr[2],
		mh->dest_addr[3],
		mh->dest_addr[4],
		mh->dest_addr[5]);

	fprintf(fp, "%d.%d.%d.%d,",
		ih->daddr[0],
		ih->daddr[1],
		ih->daddr[2],
		ih->daddr[3]);

	fprintf(fp, "%d\n", header->len);

	fclose(fp);

	printf("\n");

	//struct timeval *old_ts = (struct timeval *)param;

	u_int delay;
	LARGE_INTEGER Bps, Pps;

	/* �Ժ��������һ�β������ӳ�ʱ�� */
	/* ���ֵͨ����������ʱ������ */
	//printf("%d\n",time(&timep)- old_time );
	all_len += header->len;
	if (count != 0)
	{
		if (time(&timep) - old_time > 1) 
		{
			Bps.QuadPart = all_len / (time(&timep) - old_time) * 8;
			printf("BPS=%I64u ", Bps.QuadPart);
			if (Bps.QuadPart > 1500)
			{
				printf("[");
				printf("%d-%d-%d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
				strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

				//fprintf(fp, "%s,", timestr);

				printf("] ");
				printf("[");
				for (int i = 0; i < 6; i++) {
					printf("%02X ", mh->src_addr[i]);
				}

				for (int i = 0; i < 4; i++) {
					printf("%d.", ih->saddr[i]);
				}
				printf("] SEND ");
				printf("%I64u", Bps.QuadPart);
				printf(" bytes of limits\n");

				printf("[");
				printf("%d-%d-%d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
				strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
				printf("] ");
				printf("[");
				for (int i = 0; i < 6; i++) {
					printf("%02X ", mh->dest_addr[i]);
				}
				for (int i = 0; i < 4; i++) {
					printf("%d.", ih->daddr[i]);
				}
				printf("] SEND ");
				printf("%I64u", Bps.QuadPart);
				printf(" bytes of limits\n");

				//fprintf(fp, "%s,", timestr);


				//fprintf(fp, "%02X-%02X-%02X-%02X-%02X-%02X,",
				//	mh->src_addr[0],
				//	mh->src_addr[1],
				//	mh->src_addr[2],
				//	mh->src_addr[3],
				//	mh->src_addr[4],
				//	mh->src_addr[5]);

				//fprintf(fp, "%d.%d.%d.%d,",
				//	ih->saddr[0],
				//	ih->saddr[1],
				//	ih->saddr[2],
				//	ih->saddr[3]);

				//fprintf(fp, "%02X-%02X-%02X-%02X-%02X-%02X,",
				//	mh->dest_addr[0],
				//	mh->dest_addr[1],
				//	mh->dest_addr[2],
				//	mh->dest_addr[3],
				//	mh->dest_addr[4],
				//	mh->dest_addr[5]);

				//fprintf(fp, "%d.%d.%d.%d,",
				//	ih->daddr[0],
				//	ih->daddr[1],
				//	ih->daddr[2],
				//	ih->daddr[3]);

				//fprintf(fp, "%d\n", header->len);


			}
			all_len = 0;
			old_time = time(&timep);
		}

	}

	old_ts.tv_sec = header->ts.tv_sec;
	old_ts.tv_usec = header->ts.tv_usec;
	count++;

}


