#include <stdio.h>

int main()
{
	short x = 0xABCD;
	char y[2] = { 0xAB, 0xCD };
	printf("%x %x\n", y[0], y[1]);
	printf("%x %x\n", (char *)&x[0], (char *)&x[1]);
}

