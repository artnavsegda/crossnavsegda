#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

char buf[1000];

void process(char *buf, int numread, int sock)
{
	int numwrite = 0;
	printf("recv %d bytes\n",numread);
	for (int i=0; i<numread;i++)
	{
		printf("0x%02X ",buf[i]);
	}
	printf("\n");

	int payloadLength = buf[2];
	printf("payload length %d\n",payloadLength);

	char * payload = &buf[3];

	switch (buf[0])
	{
		case 0x0f:
			puts("Client registration request");
			numwrite = send(sock, "\x01\x00\x0b\x00\x00\x00\x00\x00" "\x03" "\x40\xff\xff\xf1\x01", 14, 0);
		case 0x02:
			puts("registration result");
			if (payloadLength == 4 && (memcmp(payload,"\x00\x00\x00\x1f",4) == 0))
			{
				puts("registration ok");
				numwrite = send(sock, "\x05\x00\x05\x00\x00\x02\x03\x00", 8, 0);
			}
		break;
		case 0x05:
			puts("data");
		break;
		case 0x0D:
			puts("heartbeat");
		default:
		break;
	}

	if (numwrite > 0)
		printf("%d bytes sent\n", numwrite);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		puts("usage: cipcontrol <ipaddr>");
		return 0;
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
		.sin_addr.s_addr = inet_addr(argv[1]),
		.sin_family = AF_INET,
		.sin_port = htons(41794)
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

	int numread = 0;
	do {
		numread = recv(sock,buf,1000,0);
		process(buf,numread,sock);
	} while (numread > 0);

       	if (numread == -1)
	{
		perror("recv error");
	}
	else
	{
		printf("recv %d bytes ok\n");
	}

	shutdown(sock, 2);
	close(sock);

	return 0;
}

