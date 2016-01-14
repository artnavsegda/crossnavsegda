#include <stdio.h>
#include <sys/socket.h>

int main()
{
	int sock;
	struct sockaddr server;
	server.sa_family = AF_INET;
	memset(&server,0,sizeof(server));
	sock = socket(PF_INET,SOCK_STREAM,0);
	if (sock < 0)
	{
		printf("socket error\n");
		exit(0);
	}
	return 0;
}

