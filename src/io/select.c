#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(STDIN_FILENO,&rfds);
	struct timeval tv = { .tv_sec = 3, .tv_usec = 0 };
	select(1,&rfds,NULL,NULL,&tv);

	if (FD_ISSET(STDIN_FILENO, &rfds))
		printf("key press\n");
	else
		printf("timeout\n");
}

