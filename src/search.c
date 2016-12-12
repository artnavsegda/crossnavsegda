#include <stdio.h>
#include <string.h>

char massive[] = "abcdefg";

int main(void)
{
	if (strchr(massive,'h') != NULL)
		printf("yes\n");
	else
		printf("no\n");

	return 0;
}
