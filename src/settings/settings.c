#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[] = "one=1 two=2 three=3.14 ip=192.168.1.150";

char * getopt(char *config2, char *token)
{
	static char config[100];
	strcpy(config,config2);
	char * pch = strtok(strstr(config,token),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," ");
	printf("string value %s, ",pch);
	return pch;
}

char * getip(char *config2, char *token)
{
	static char ip[4];
	ip[0] = atoi(strtok(getopt(config2,token),"."));
	ip[1] = atoi(strtok(NULL,"."));
	ip[2] = atoi(strtok(NULL,"."));
	ip[3] = atoi(strtok(NULL,"."));
	return ip;
}

int main(void)
{
	FILE * setfile = fopen("./settings.txt","r");


	printf("int value %d\n",atoi(getopt(str,"one")));
	printf("int value %d\n",atoi(getopt(str,"two")));
	printf("int value %d\n",atoi(getopt(str,"one")));
	printf("float value %f\n",atof(getopt(str,"three")));

	char *ip = getip(str,"ip");
	printf("ip %hhu.%hhu.%hhu.%hhu\n",ip[0],ip[1],ip[2],ip[3]);

	return 0;
}

