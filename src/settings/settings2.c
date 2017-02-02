#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[100] = "one=1\n\
two=2\n\
three=3.14\n\
ip=192.168.1.150";
//char str[100];

char three[]="3.141592";

char * getopt(char *config2, char *token)
{
	if (strstr(config2,token)==NULL)
		return "0";
	static char config[100];
	strcpy(config,config2);
	char * pch = strtok(strstr(config,token),"=");
	printf("token %s, ",pch);
	pch = strtok(NULL," \n");
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

char *options[100];
char *values[100];
int i = 0;
int optisize;

void setopt(char *parameter, char *newset)
{
	for (i=0;i<optisize;i++)
	{
		if (strcmp(options[i],parameter)==0)
		{
			if (strlen(newset)>strlen(values[i]))
			{
				//values[i] = newset; //just change the pointer
				values[i] = malloc(strlen(newset)); //or to allocate new memory ?
				strcpy(values[i],newset);
			}
			else
				strcpy(values[i],newset);
		}
	}
}

int main(void)
{
	options[i] = strtok(str," \n");
	while (options[i]!=NULL)
		options[++i] = strtok(NULL," \n");

	optisize = i;

	for (i=0;i<optisize;i++)
	{
//		puts(options[i]);
		strtok(options[i],"=");
		values[i] = strtok(NULL,"=");
	}

	for (i=0;i<optisize;i++)
	{
		if (strcmp(options[i],"three")==0)
			values[i] = three;
	}

	setopt("two","2.017");

	for (i=0;i<optisize;i++)
		printf("%s=%s\n",options[i],values[i]);

/*	FILE * setfile = fopen("./settings.txt","r");
	if (setfile != NULL)
	{
		fread(str,1,100,setfile);
	}*/

//	printf("one int value %d\n",atoi(getopt(str,"one")));
//	printf("two int value %d\n",atoi(getopt(str,"two")));
//	printf("one int value %d\n",atoi(getopt(str,"one")));
//	printf("three float value %f\n",atof(getopt(str,"three")));

//	char *ip = getip(str,"ip");
//	printf("ip %hhu.%hhu.%hhu.%hhu\n",ip[0],ip[1],ip[2],ip[3]);

	return 0;
}

