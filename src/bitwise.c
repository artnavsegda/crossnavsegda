#include <stdio.h>

void printbinary(unsigned char value)
{
	for (int i = 0; i < 8; i++)
		printf("%hhu", (value >> 7-i) & 0x01);
	//printf("\n");
}

void printarbin(unsigned char *value, int amount)
{
	for (int i = 0; i < amount; i++)
		printbinary(value[i]);
}

void shiftarray(unsigned char *value, int amount, int shift)
{
	for (int i = 0; i < amount; i++)
		printbinary((value[i+(shift/8)] << (shift%8)) | (value[i+(shift/8)+1] >> 8-(shift%8)));
}


void cutarray(unsigned char *value, int amount, int shift, int cut)
{
	unsigned char full = 0xFF;
	unsigned char zero = 0x00;
	unsigned char part = 0x3F;
	for (int i = 0; i < cut/8; i++)
		printbinary((value[i+(shift/8)] << (shift%8)) | (value[i+(shift/8)+1] >> 8-(shift%8)));
	printbinary(((value[(cut/8)+(shift/8)] << (shift%8)) | (value[(cut/8)+(shift/8)+1] >> 8-(shift%8))) & (0xFF << 8-(cut%8)));
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
	printf("\n");
	printbinary(zero);
	printf("\n");
	printbinary(one);
	printf("\n");
	printbinary(chet);
	printf("\n");
	printbinary(nechet);
	printf("\n");
	printarbin("hello",5);
	printf("\n");
	shiftarray("hello",5,1);
	printf("\n");
	shiftarray("hello",5,2);
	printf("\n");
	shiftarray("hello",5,3);
	printf("\n");
	shiftarray("hello",5,4);
	printf("\n");
	shiftarray("hello",5,5);
	printf("\n");
	shiftarray("hello",5,6);
	printf("\n");
	shiftarray("hello",5,7);
	printf("\n");
	shiftarray("hello",5,8);
	printf("\n");
	shiftarray("hello",5,9);
	printf("\n");
	shiftarray("hello",5,10);
	printf("\n");
	shiftarray("hello",5,11);
	printf("\n");
	cutarray("hello",5,11,11);
	printf("\n");
	cutarray("hello",5,11,10);
	printf("\n");
	cutarray("hello",5,11,9);
	printf("\n");
	cutarray("hello",5,11,8);
	printf("\n");
	cutarray("hello",5,11,7);
	printf("\n");
	cutarray("hello",5,11,6);
	printf("\n");
	cutarray("hello",5,11,5);
	printf("\n");
	cutarray("hello",5,11,4);
	printf("\n");
	cutarray("hello",5,11,3);
	printf("\n");
	cutarray("hello",5,11,2);
	printf("\n");
	cutarray("hello",5,11,1);
	printf("\n");

	return 0;
}
