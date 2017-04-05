#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>

#define NTP_TIME_OFFSET 2208988800

struct ntptime {
	unsigned int timeseconds;
	unsigned int timefraction;
};

struct ntpframe {
	unsigned char leapvermode;
	unsigned char stratumlevel;
	unsigned char poll;
	unsigned char precision;
	unsigned int rootdelay;
	unsigned int driftrate;
	unsigned int referenceid;
	struct ntptime reference;
	struct ntptime origin;
	struct ntptime receive;
	struct ntptime transmit;
};

struct ntpframe myframe;

char package[] = { 0xE3, 0x00, 0x03, 0xFA, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x8D, 0x97, 0xBA, 0x2C, 0x64, 0xE9, 0xCF };

int main()
{
	unsigned char buf[100];
	int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	int sock2 = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
	{
		printf("socket ok\n");
	}

	struct sockaddr_in other = {
		//.sin_addr.s_addr = inet_addr("192.168.1.110"),
		.sin_addr.s_addr = inet_addr("132.163.4.103"),
		.sin_family = AF_INET,
		.sin_port = htons(123)
	};

	int slen = sizeof(other);

	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port = htons(123)
	};

	if (bind(sock,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		perror("bind error");
		close(sock);
		return 1;
	}
	else
	{
		printf("bind ok\n");
	}

	int numwrite = sendto(sock,package,sizeof(package),0,(struct sockaddr *)&other, slen);
	if (numwrite == -1)
	{
		perror("sendto error");
	}
	else
	{
		printf("send %d bytes\n",numwrite);
	}

	int numread = recvfrom(sock,&myframe,48,0,(struct sockaddr *)&other, &slen);
	if (numread == -1)
	{
		perror("recv error");
	}
	else
	{
		printf("Unixtime: %ld\n",time(NULL));
		printf("NTP time: %ld\n",time(NULL)+NTP_TIME_OFFSET);
		printf("recv %d bytes\n",numread);
		printf("NTP frame: %ld\n",sizeof(myframe));
		printf("NTP lvm: 0x%X\n",myframe.leapvermode);
		printf("NTP stratum: 0x%X\n",myframe.stratumlevel);
		printf("NTP poll: 0x%X\n",myframe.poll);
		printf("NTP precision: 0x%X\n",myframe.precision);
		printf("NTP root delay: 0x%X\n",myframe.rootdelay);
		printf("NTP drift rate: 0x%X\n",myframe.driftrate);
		printf("NTP reference id: 0x%X\n",myframe.referenceid);
		printf("NTP reference time: 0x%X\n",myframe.reference.timeseconds);
		printf("NTP reference fraction: 0x%X\n",myframe.reference.timefraction);
		printf("NTP origin time: %u\n",myframe.origin.timeseconds-NTP_TIME_OFFSET);
		printf("NTP origin fraction: 0x%X\n",myframe.origin.timefraction);
		printf("NTP receive time: %u\n",myframe.receive.timeseconds-NTP_TIME_OFFSET);
		printf("NTP receive fraction: 0x%X\n",myframe.receive.timefraction);
		printf("NTP transmit time: %u\n",myframe.transmit.timeseconds-NTP_TIME_OFFSET);
		printf("NTP transmit fraction: %u\n",myframe.transmit.timefraction);
		printf("\n");
	}

	if (shutdown(sock, 2) == -1)
	{
		perror("shutdown error");
		close(sock);
		return 1;
	}
	else
	{
		printf("shutdown ok\n");
	}
	close(sock);

	return 0;
}
