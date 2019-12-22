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
	int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
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

	while(1)
	{
		int numread = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&other, &slen);

		if (numread == -1)
		{
			perror("recv error");
		}
		else
		{
      printf("port %d\n", other.sin_port);


			printf("recv %d bytes\n",numread);
			for (int i=0; i<numread;i++)
			{
				printf("0x%02X, ",buf[i]);
			}
			printf("\n");
      char line[10];
      snprintf(line, 10, "%%.%ds\n",numread);
      printf(line,buf);
		}
	}

	shutdown(sock, 2);
	close(sock);

	return 0;
}
