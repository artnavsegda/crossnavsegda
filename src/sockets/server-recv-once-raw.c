#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

int main()
{
	unsigned char buf[100];
	int sock = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
	{
		printf("socket ok\n");
	}

	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port = htons(1100)
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

	if (listen(sock,10) == -1)
	{
		perror("listen error");
		close(sock);
		return 1;
	}
	else
	{
		printf("listen ok\n");
	}

		int msgsock = accept(sock,NULL,NULL);
		if (msgsock == -1)
		{
			perror("accept error");
			close(sock);
			return 1;
		}
		else
		{
			printf("accept ok\n");
		}

		int numread = recv(msgsock,buf,100,0);
		if (numread == -1)
		{
			perror("recv error");
		}
		else
		{
			printf("recv %d bytes\n",numread);
			for (int i=0; i<numread;i++)
			{
				printf("0x%02X ",buf[i]);
			}
			printf("\n");
		}

		if (shutdown(msgsock, 2) == -1)
		{
			perror("shutdown error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("shutdown ok\n");
		}
		close(msgsock);
	close(sock);

	return 0;
}
