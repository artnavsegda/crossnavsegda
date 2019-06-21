#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/time.h>

void timer_handler(int signal)
{
	printf("alarm\n");
}

int main (void)
{
	struct pollfd fds[1];
	int ret;
	struct timespec timeout = { .tv_sec = 3 };
	struct itimerval it_val = { .it_value = { .tv_sec = 3 }, .it_interval = { .tv_sec = 5 }};
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask,SIGALRM);
	signal(SIGALRM, timer_handler);
	setitimer(ITIMER_REAL, &it_val, NULL);

	/* watch stdin for input */
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	while(1)
	{
		ret = ppoll(fds, 1, &timeout, &mask);
		if (ret == -1) {
			perror ("poll");
			return 1;
		}
		if (!ret) {
			printf ("time out\n");
		}
		if (fds[0].revents & POLLIN)
		{
			char buf[100];
			int len = read(STDIN_FILENO, buf, 100);
			printf ("stdin is readable\n");
		}
	}

	return 0;
}
