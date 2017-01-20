#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = "one=1 two=2 three=3";
	char * pch = strtok(strstr(str,"two"),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("value %s\n",pch);
	return 0;
}

