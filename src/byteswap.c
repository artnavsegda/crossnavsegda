#include <arpa/inet.h>
#include <stdio.h>

int main(void)
{
	unsigned short i = 0xABCD;

	printf("original is 0x%04X\n", i);
	printf("htons 0x%04X\n", htons(i));
	printf("ntohs 0x%04X\n", ntohs(i));

	return 0;
}
