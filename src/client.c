#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock < 0)
	{
		printf("socket error\n");
		exit(0);
	}
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(1100);
	//inet_pton(AF_INET, "192.168.1.105", &client.sin_addr);
	inet_pton(AF_INET, "127.0.0.1", &client.sin_addr);
	if (connect(sock,&client,sizeof client) == -1)
	{
		printf("connect error\n");
		close(sock);
		exit(0);
	}

	write(sock,"hello",6);

	shutdown(sock, SHUT_RDWR);
	close(sock);

	return 0;
}

