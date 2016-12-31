#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <byteswap.h>

char buf[100];
char ask[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x32, 0x03, 0x00, 0x00, 0x00, 0x01 };

struct tcpframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
};

struct pduframestruct {
	unsigned char unitid;
	unsigned char fncode;
	unsigned short data[256];
};

struct tcpframestruct tcpframe = {
	.tsid = 1,
	.protoid = 0,
	.length = 6,
};

struct pduframestruct pduframe = {
	.unitid = 50,
	.fncode = 3,
};

struct tcpframestruct askframe;
struct pduframestruct askpduframe;

struct mbframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
	unsigned char unitid;
	unsigned char fncode;
	unsigned short data[2];
};

struct mbframestruct mbframe = {
	.tsid = 0x0100,
	.protoid = 0x0000,
	.length = 0x0600,
	.unitid = 50,
	.fncode = 3,
	.data = { 0x0000, 0x0100 }
};

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("name function code and both values\n");
		return 1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
	{
		printf("socket ok\n");
	}
	struct sockaddr_in client = {
		.sin_addr.s_addr = inet_addr("127.0.0.1"),
		.sin_family = AF_INET,
		.sin_port = htons(1100)
	};
	if (connect(sock,(struct sockaddr *)&client, sizeof(client)) == -1)
	{
		perror("connect error");
		close(sock);
		return 1;
	}
	else
	{
		printf("connect ok\n");
	}

	//int numwrite = send(sock,ask,12,0);
	
	sscanf(argv[1],"%hhu",&mbframe.fncode); // <-----
	sscanf(argv[2],"%hu",&mbframe.data[0]);
	mbframe.data[0] = bswap_16(mbframe.data[0]);
	sscanf(argv[3],"%hu",&mbframe.data[1]);
	mbframe.data[1] = bswap_16(mbframe.data[1]);

	int numwrite = send(sock,&mbframe,12,0);
	if (numwrite == -1)
	{
		perror("send error");
	}
	else
	{
		printf("send %d bytes ok\n", numwrite);
	}

	int numread = recv(sock,buf,100,0);
	if (numread == -1)
	{
		perror("recv error");
		close(sock);
		return 1;
	}
	else
	{
		printf("recv %d bytes\n",numread);
		for (int i=0; i<numread;i++)
		{
			printf("0x%02hhX ",buf[i]);
		}
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

