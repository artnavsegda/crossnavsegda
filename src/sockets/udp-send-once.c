#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

char package[] = { 0xE3, 0x00, 0x03, 0xFA, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x8D, 0x97, 0xBA, 0x2C, 0x64, 0xE9, 0xCF };

int main()
{
	unsigned char buf[100];
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

	struct sockaddr_in other = {
		.sin_addr.s_addr = inet_addr("192.168.1.110"),
		.sin_family = AF_INET,
		.sin_port = htons(123)
	};

	int slen = sizeof(other);

	int numwrite = sendto(sock,package,sizeof(package),0,(struct sockaddr *)&other, slen);
	if (numwrite == -1)
	{
		perror("sendto error");
	}
	else
	{
		printf("send %d bytes\n",numwrite);
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

