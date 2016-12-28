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
	struct addrinfo hints = {
		.ai_family = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM,
		.ai_protocol = IPPROTO_TCP
	};
	struct addrinfo *result;
	getaddrinfo("127.0.0.1", "1100", &hints, &result);
	int sock = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	if (sock == -1)
	{
		perror("socket error");
		freeaddrinfo(result);
		return 1;
	}
	struct sockaddr_in client = {
		.sin_family = AF_INET,
		.sin_port = htons(1100)
	};
	inet_pton(AF_INET, "127.0.0.1", &client.sin_addr);
	if (connect(sock,result->ai_addr,result->ai_addrlen) == -1)
	{
		perror("connect error");
		close(sock);
		return 1;
	}

	send(sock,"hello",6,0);

	shutdown(sock, SHUT_RDWR);
	close(sock);

	return 0;
}

