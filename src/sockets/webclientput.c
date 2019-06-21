#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

char buf[1000] = "Goodbuy cruel world\n\n";
char ask[] = "PUT /hello HTTP/1.0\n\n";
//char ask[] = "GET /main.js HTTP/1.0\n\n";
//char ask[] = "GET /main.css HTTP/1.0\n\n";

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
		//.sin_addr.s_addr = inet_addr("192.168.1.150"),
		.sin_family = AF_INET,
		.sin_port = htons(80)
		//.sin_port = htons(1100)
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

	int numwrite = send(sock,ask,strlen(ask),0);
	if (numwrite == -1)
	{
		perror("send error");
	}
	else
	{
		printf("send %d bytes ok\n", numwrite);
		for (int i=0; i<numwrite;i++)
		{
			printf("%c",ask[i]);
		}
		printf("\n");
	}

	numwrite = send(sock,buf,strlen(buf),0);
	if (numwrite == -1)
	{
		perror("send error");
	}
	else
	{
		printf("send %d bytes ok\n", numwrite);
		for (int i=0; i<numwrite;i++)
		{
			printf("%c",buf[i]);
		}
		printf("\n");
	}

	int numread = recv(sock,buf,1000,0);
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
			printf("%c",buf[i]);
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

