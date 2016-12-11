#include <stdio.h>
#include <time.h>

int main(void)
{
	struct timespec timenow;
	clock_gettime(CLOCK_REALTIME, &timenow);
	printf("%d.%d\n",timenow.tv_sec,timenow.tv_nsec);
}

