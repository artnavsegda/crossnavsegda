#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void timer_handler(int signal)
{
	printf("alarm\n");
}

int main(void)
{
	struct itimerval it_val;
	signal(SIGALRM, timer_handler);
	it_val.it_value.tv_sec = 3;
	it_val.it_value.tv_usec = 0;
	it_val.it_interval = it_val.it_value;
	setitimer(ITIMER_REAL, &it_val, NULL);
	while (1)
		sleep(1);
	return 0;
}
