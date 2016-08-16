#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int modenumber = 0;

void alarm_handler(int signal)
{
	printf("alarm\n");
	alarm(10);
}

void entermode(int modetoenter)
{
	modenumber = modetoenter;
}

int main(void)
{
	signal(SIGALRM, alarm_handler);
	entermode(1);
	alarm(10);
	while (1)
		sleep(1);
	return 0;
}

