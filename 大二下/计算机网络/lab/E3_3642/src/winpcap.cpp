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


/* 4字节的IP地址 */
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

/* UDP 首部*/
typedef struct udp_header {
	u_short sport;          // 源端口(Source port)
	u_short dport;          // 目的端口(Destination port)
	u_short len;            // UDP数据包长度(Datagram length)
	u_short crc;            // 校验和(Checksum)
}udp_header;

/* 回调函数原型 */
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

	/* 获得设备列表 */
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	//findalldevs_ex(char *source, struct pcap_rmtauth *auth, pcap_if_t **alldevs, char *errbuf  )
	//source 可以是”rpcap://”，表示本地适配器；#define PCAP_SRC_IF_STRING “rpcap://” 
	//auth:指向pcap_rmtauth结构的指针，用来保存连接到远程主机上授权信息。在查询本地机器时，此参数没什么意义，可以为NULL。
	//alldevs: 指向pcap_if_t结构的指针，此函数返回时，该指针被设置为所获得的设备接口列表的第一个元素，列表的每一个元素都是Pcap_if_t结构。
	//返回值：成功返回0，alldevs返回设备列表，alldevs不会为NULL。否则返回－1，那就是说系统没有任何接口可以列举的。出错的消息在errbuf里面返回

	/* 打印列表 */
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
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 跳转到已选设备 */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* 打开适配器 */
	if ((adhandle = pcap_open(d->name,  // 设备名
		65536,     // 要捕捉的数据包的部分 
				   // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,         // 混杂模式
		1000,      // 读取超时时间
		NULL,      // 远程机器验证
		errbuf     // 错误缓冲池
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 检查数据链路层，为了简单，我们只考虑以太网 */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	if (d->addresses != NULL)
		/* 获得接口第一个地址的掩码 */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* 如果接口没有地址，那么我们假设一个C类的掩码 */
		netmask = 0xffffff;


	//编译过滤器
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	//设置过滤器
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}


	time(&timep);
	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间 
	oldtime = timep;
	old_time = time(&oldtime);

	printf("\nlistening on %s...\n", d->description);

	/* 释放设备列表 */
	pcap_freealldevs(alldevs);

	/* 开始捕捉 */
	pcap_loop(adhandle, 0, packet_handler, NULL);

	return 0;
}

/* 回调函数，当收到每一个数据包时会被libpcap所调用 */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	struct tm* ltime;
	char timestr[16];
	mac_header* mh;
	ip_header* ih;
	time_t local_tv_sec;

	FILE* fp = fopen("Listen_MAC_IP.csv", "a+");

	time(&timep);
	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间
	printf("%d-%d-%d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);


	/* 将时间戳转换成可识别的格式 */
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
	printf("%s  ", timestr);

	/* 打印数据包的长度 */
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

	/* 以毫秒计算上一次采样的延迟时间 */
	/* 这个值通过采样到的时间戳获得 */
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


