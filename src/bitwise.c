#include <stdio.h>

void printbinary(unsigned char value)
{
	for (int i = 0; i < 8; i++)
		printf("%hhu", (value >> 7-i) & 0x01);
	printf("\n");
}

int main(void)
{
	unsigned char chet = 0xAA;
	unsigned char nechet = 0x55;
	unsigned char zero = 0x00;
	unsigned char full = 0xFF;
	unsigned char one = 0x01;
	printf("chet 0x%02X\n",chet);
	printf("~chet 0x%02hhX\n",~chet);
	printf("chet >> 1 0x%02X\n",chet >> 1);
	printf("nechet 0x%02X\n",nechet);
	printf("~nechet 0x%02hhX\n",~nechet);
	printf("nechet << 1 0x%02X\n",nechet << 1);
	printf("chet & nechet 0x%02X\n",chet & nechet);
	printf("chet | nechet 0x%02X\n",chet | nechet);
	printf("zero 0x%02X\n",zero);
	printf("~zero 0x%02hhX\n",~zero);
	printf("full 0x%02X\n",full);
	printf("~full 0x%02hhX\n",~full);
	printf("full >> 1 0x%02X\n",full >> 1);
	printf("one 0x%02X\n",one);
	printf("~one 0x%02hhX\n",~one);
	printf("one << 1 0x%02X\n",one << 1);

	printbinary(full);
	printbinary(zero);
	printbinary(one);
	printbinary(chet);
	printbinary(nechet);

	return 0;
}
