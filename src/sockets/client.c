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
		perror("socket error");
		return 1;
	}
	struct sockaddr_in client = {
		.sin_family = AF_INET,
		.sin_port = htons(1100)
	};
	inet_pton(AF_INET, "127.0.0.1", &client.sin_addr);
	if (connect(sock,(struct sockaddr *)&client,sizeof(client)) == -1)
	{
		perror("connect error");
		close(sock);
		return 1;
	}

	write(sock,"hello",6);

	shutdown(sock, SHUT_RDWR);
	close(sock);

	return 0;
}

