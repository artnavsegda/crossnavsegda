#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

char buf[100];
char ask[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x32, 0x03, 0x00, 0x00, 0x00, 0x01 };

struct tcpframestruct {
	unsigned short tsid;
	unsigned short protocolid;
	unsigned short length;
};

struct pduframestruct {
	unsigned char unitid;
	unsigned char fncode;
};

struct tcpframestruct tcpframe;
unsigned char framebuf;

int main()
{
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

	int numwrite = send(sock,ask,12,0);
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

