#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signal)
{
	printf("alarm\n");
}

int main(void)
{
	signal(SIGALRM, alarm_handler);
	alarm(10);
	while (1)
		sleep(1);
	return 0;
}
