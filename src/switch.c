#include <stdio.h>

int main(void)
{
	int i = 2;
	switch(i)
	{
		case 1:
			printf("one\n");
		break;
		case 2:
			printf("two\n");
		break;
		case 3:
			printf("three\n");
		break;
		default:
			printf("default\n");
		break;
	}
	return 0;
}
