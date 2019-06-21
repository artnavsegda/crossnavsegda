#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[1000] = "one=1\n\
two=2\n\
three=3.14\n\
ip=192.168.1.150";

char three[]="3.141592";

char * getip(char *token)
{
	static char ip[4];
	char *temp = malloc(strlen(token));
	strcpy(temp,token);
	ip[0] = atoi(strtok(temp,"."));
	ip[1] = atoi(strtok(NULL,"."));
	ip[2] = atoi(strtok(NULL,"."));
	ip[3] = atoi(strtok(NULL,"."));
	free(temp);
	return ip;
}

char *options[100];
char *values[100];
int i = 0;
int optisize;

void setopt(char *parameter, char *newset)
{
	int found = 0;
	for (i=0;i<optisize;i++)
	{
		if (strcmp(options[i],parameter)==0)
		{
			if (strlen(newset)>strlen(values[i]))
			{
				found = 1;
				//values[i] = newset; //just change the pointer
				values[i] = malloc(strlen(newset)); //or to allocate new memory ?
				strcpy(values[i],newset);
			}
			else
				strcpy(values[i],newset);
		}
	}
	if (found == 0)
	{
		options[optisize] = parameter;
		values[optisize] = newset;
		optisize++;
	}
}

char * getopt(char *parameter)
{
	for (i=0;i<optisize;i++)
		if (strcmp(options[i],parameter)==0)
			return values[i];
	return NULL;
}

int main(void)
{
	FILE * setfile = fopen("./settings.txt","r");
	if (setfile != NULL)
	{
		int numread = fread(str,1,1000,setfile);
		printf("read %d bytes\n",numread);
		str[numread] = '\0';
	}

	options[i] = strtok(str," \n");
	while (options[i]!=NULL)
	{
		puts(options[i]);
		options[++i] = strtok(NULL," \n");
	}

	optisize = i;

	printf("aquired %d pairs\n",optisize);


	for (i=0;i<optisize;i++)
	{
		strtok(options[i],"=");
		values[i] = strtok(NULL,"=");
	}

	for (i=0;i<optisize;i++)
	{
		if (strcmp(options[i],"three")==0)
			values[i] = three;
	}

	setopt("two","2.017");
	setopt("four","4.04");

	for (i=0;i<optisize;i++)
		printf("%s=%s\n",options[i],values[i]);

//	printf("one int value %d\n",atoi(getopt(str,"one")));
//	printf("two int value %d\n",atoi(getopt(str,"two")));
//	printf("one int value %d\n",atoi(getopt(str,"one")));
//	printf("three float value %f\n",atof(getopt(str,"three")));

//	char *ip = getip(str,"ip");
//	printf("ip %hhu.%hhu.%hhu.%hhu\n",ip[0],ip[1],ip[2],ip[3]);

	return 0;
}
