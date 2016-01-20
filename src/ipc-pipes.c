#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define DATA "hello wicked world"

int main()
{
	int sockets[2], child;

	if (pipe(sockets) < 0)
	{
		perror("opening stram socket pair");
		exit(1);
	}

	child = fork();

	if (child == -1)
	{
		perror("fork");
		exit(1);
	}

	if (child)
	{
		char buf[1024];
		close(sockets[1]);
		read(sockets[0], buf, 1024);
		printf("%s\n", buf);
		close(sockets[0]);
	}
	else
	{
		close(sockets[0]);
		write(sockets[1], DATA, sizeof(DATA));
		close(sockets[1]);
	}

	return 0;
}

