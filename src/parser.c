#include <stdio.h>
#include <string.h>

char example[] = "one=1\n\
two=2\n\
three=3";

int main(void)
{
	char * pch = strtok(example,"\n");
	while (pch != NULL)
	{
		printf("token %s\n",pch);
		printf("parameter %s\n",strtok(pch,"="));
		printf("value %s\n",strtok(NULL,"="));
		pch = strtok(NULL,"\n");
	}
	return 0;
}
