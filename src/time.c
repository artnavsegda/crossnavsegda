#include <stdio.h>
#include <time.h>

#define NTP_TIME_OFFSET 2208988800

struct ntptime {
	unsigned int timeseconds;
	unsigned int timefraction;
};

struct ntpframe {
	unsigned char leapvermode;
	unsigned char stratumlevel;
	unsigned char poll;
	unsigned char precision;
	unsigned int rootdelay;
	unsigned int driftrate;
	unsigned int referenceid;
	struct ntptime reference;
	struct ntptime origin;
	struct ntptime receive;
	struct ntptime transmit;
};

int main(void)
{
	time_t timenow;
	timenow = time(NULL);
	printf("Unixtime: %ld\n",timenow);
	printf("NTP time: %ld\n",timenow+NTP_TIME_OFFSET);
	printf("NTP frame: %ld\n",sizeof(struct ntpframe));
}

