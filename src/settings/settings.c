#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[] = "one=1 two=2 three=3.14";


char * getopt(char *config2, char *token)
{
	char config[100];
	strcpy(config,config2);
	char * pch = strtok(strstr(config,token),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("string value %s, ",pch);
	return pch;
}

int main(void)
{
/*	char * pch = strtok(strstr(str,"two"),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("string value %s, ",pch);
	printf("int value %d\n",atoi(pch)); 

	pch = strtok(strstr(str,"three"),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("string value %s, ",pch);
	printf("float value %f\n",atof(pch));*/

	printf("int value %d\n",atoi(getopt(str,"one")));
	printf("int value %d\n",atoi(getopt(str,"two")));
	printf("int value %d\n",atoi(getopt(str,"one")));
	printf("float value %f\n",atof(getopt(str,"three")));

	return 0;
}

