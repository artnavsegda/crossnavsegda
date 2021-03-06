#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		puts("usage: program <port>");
		return 0;
	}

	unsigned char buf[1000];
	int sock = socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
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
		.sin_port = htons(atoi(argv[1]))
	};

	struct sockaddr_in other;
	int slen = sizeof(other);

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

	int numread = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&other, &slen);
	if (numread == -1)
	{
		perror("recv error");
	}
	else
	{
		printf("recv %d bytes\n",numread-28);
		printf("destinaton port %hhu %hhu\n",buf[22],buf[23]);

		for (int i=28; i<numread;i++)
		{
			printf("0x%02X, ",buf[i]);
		}
		printf("\n");
	}

	shutdown(sock, 2);
	close(sock);

	return 0;
}
