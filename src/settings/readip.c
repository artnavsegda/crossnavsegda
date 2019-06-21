#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ipin[] = "192.168.1.150";
unsigned char ip[4];
char macin[] = "de:ad:be:ef:fe:ed";
char mac[6];

int main(void)
{
	ip[0] = atoi(strtok(ipin,"."));
	ip[1] = atoi(strtok(NULL,"."));
	ip[2] = atoi(strtok(NULL,"."));
	ip[3] = atoi(strtok(NULL,"."));

	printf("%hhu.%hhu.%hhu.%hhu\n",ip[0],ip[1],ip[2],ip[3]);

	return 0;
}

