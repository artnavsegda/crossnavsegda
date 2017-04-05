#include <stdio.h>
#include <string.h>
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

struct ntpframe myframe;

char myframe2[] = { 0xE3, 0x00, 0x03, 0xFA, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x8D, 0x97, 0xBA, 0x2C, 0x64, 0xE9, 0xCF };

int main(void)
{
	memcpy(&myframe,&myframe2,48);
	time_t timenow;
	timenow = time(NULL);
	printf("Unixtime: %ld\n",timenow);
	printf("NTP time: %ld\n",timenow+NTP_TIME_OFFSET);
	printf("NTP frame: %ld\n",sizeof(myframe));
	printf("NTP lvm: 0x%X\n",myframe.leapvermode);
	printf("NTP stratum: 0x%X\n",myframe.stratumlevel);
	printf("NTP poll: 0x%X\n",myframe.poll);
	printf("NTP precision: 0x%X\n",myframe.precision);
	printf("NTP root delay: 0x%X\n",myframe.rootdelay);
	printf("NTP drift rate: 0x%X\n",myframe.driftrate);
	printf("NTP reference id: 0x%X\n",myframe.referenceid);
	printf("NTP reference time: 0x%X\n",myframe.reference.timeseconds);
	printf("NTP reference fraction: 0x%X\n",myframe.reference.timefraction);
	printf("NTP origin time: 0x%X\n",myframe.origin.timeseconds);
	printf("NTP origin fraction: 0x%X\n",myframe.origin.timefraction);
	printf("NTP receive time: 0x%X\n",myframe.receive.timeseconds);
	printf("NTP receive fraction: 0x%X\n",myframe.receive.timefraction);
	printf("NTP transmit time: %u\n",myframe.transmit.timeseconds-NTP_TIME_OFFSET);
	printf("NTP transmit fraction: %u\n",myframe.transmit.timefraction);
}

