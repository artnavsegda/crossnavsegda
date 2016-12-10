#include <stdio.h>

int main(void)
{
	struct eeprom
	{
		unsigned char ip[4];
		unsigned char mac[6];
	};
	struct eeprom e;
	scanf("ip = %hhu.%hhu.%hhu.%hhu\n",&e.ip[0],&e.ip[1],&e.ip[2],&e.ip[3]);
	scanf("mac = %hhx:%hhx:%hhx:%hhx:%hhx:%hhx\n",&e.mac[0],&e.mac[1],&e.mac[2],&e.mac[3],&e.mac[4],&e.mac[5]);
	fputs((char *)&e,stdout);
	return 0;
}

