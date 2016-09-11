#include <stdio.h>

int main(void)
{
	struct eeprom
	{
		unsigned char ip[4];
		unsigned char mac[6];
		unsigned short length_table[13];
		unsigned char jump_table[13];
	};
	struct eeprom e;
	fgets((char *)&e,sizeof(e),stdin);
	printf("ip = %hhu.%hhu.%hhu.%hhu\n",e.ip[0],e.ip[1],e.ip[2],e.ip[3]);
	printf("mac = %hhx:%hhx:%hhx:%hhx:%hhx:%hhx\n",e.mac[0],e.mac[1],e.mac[2],e.mac[3],e.mac[4],e.mac[5]);
	printf("startlevel = %hu\nprecalibrationdelay = %hu\ncalibration = %hu\npostcalibrationdelay = %hu\ncelldelay = %hu\ncelllevel = %hu\nzerodelay = %hu\nzerotest = %hu\ntotalmercurydelay = %hu\ntotalmercury = %hu\nelementalmercurydelay = %hu\nelementalmercury = %hu\npurge = %hu\n",e.length_table[0],e.length_table[1],e.length_table[2],e.length_table[3],e.length_table[4],e.length_table[5],e.length_table[6],e.length_table[7],e.length_table[8],e.length_table[9],e.length_table[10],e.length_table[11],e.length_table[12]);
	return 0;
}

