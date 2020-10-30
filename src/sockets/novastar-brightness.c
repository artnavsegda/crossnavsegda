#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		puts("usage: novastar-brightness <ipaddr>");
		return 0;
	}

	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
		.sin_port = htons(5200)
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

	char payload[] = { 0x55,0xAA,0x00,0x00,0xFE,0xFF,0x01,0xFF,0xFF,0xFF,0x01,0x00,0x01,0x00,0x00,0x02,0x01,0x00,0x80,0xD5,0x5A };

	int numwrite = send(sock,payload,21,0);

	if (numwrite == -1)
	{
		perror("send error");
	}
	else
	{
		printf("send %d bytes ok\n", numwrite);
	}

	shutdown(sock, 2);
	close(sock);

	return 0;
}

