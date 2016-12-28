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
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
		.ai_protocol = IPPROTO_TCP,
		.ai_flags = AI_PASSIVE
	};
	struct addrinfo *result;
	getaddrinfo(NULL,"1100",&hints,&result);

	int buf[100];
	int sock = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	if (sock == -1)
	{
		perror("socket error");
		freeaddrinfo(result);
		return 1;
	}
	if (bind(sock,result->ai_addr,result->ai_addrlen) == -1)
	{
		perror("bind error");
		freeaddrinfo(result);
		close(sock);
		return 1;
	}
	if (listen(sock,10) == -1)
	{
		perror("listen error");
		close(sock);
		return 1;
	}

	while(1)
	{
		int msgsock = accept(sock,NULL,NULL);
		if (msgsock == -1)
		{
			perror("accept error");
			close(sock);
			return 1;
		}
		recv(msgsock,buf,100,0);
		if (shutdown(msgsock, SHUT_RDWR) == -1)
		{
			perror("shutdown error");
			close(msgsock);
			close(sock);
			return 1;
		}
		close(msgsock);
	}
	close(sock);

	return 0;
}

