#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>

void sig_handler(int signum)
{
	printf("io\n");
}

int main(void)
{
	signal(SIGIO, &sig_handler);
	fcntl(STDIN_FILENO, F_SETOWN, getpid());
	fcntl(STDIN_FILENO, F_SETFL, FASYNC);

	while(1);
}
