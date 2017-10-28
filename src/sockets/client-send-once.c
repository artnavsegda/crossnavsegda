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

	int numwrite = send(sock,"hello",6,0);

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

