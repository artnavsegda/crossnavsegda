#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[] = "one=1 two=2 three=3.14";

int main(void)
{
	char * pch = strtok(strstr(str,"two"),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("string value %s, ",pch);
	printf("int value %d\n",atoi(pch)); 

	pch = strtok(strstr(str,"three"),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("string value %s, ",pch);
	printf("float value %f\n",atof(pch));

	return 0;
}

