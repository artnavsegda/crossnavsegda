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
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	memset(&server,0,sizeof(server));
	int sock = socket(PF_INET,SOCK_STREAM,0);
	if (sock < 0)
	{
		printf("socket error\n");
		exit(0);
	}
	return 0;
}

