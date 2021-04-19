#include <stdio.h>
#include <string.h>

char *comms[] = {"one","two","three","four"};

int main()
{
	int i;
	char buf[100];
	while (scanf("%s", buf)!=EOF)
	{
		for(i = 0; i < 4; i++)
			if (strcmp(buf,comms[i])==0)
				break;
		switch(i)
		{
			case 0:
				printf("1\n");
			break;
			case 1:
				printf("2\n");
			break;
			case 2:
				printf("3\n");
			break;
			case 3:
				printf("4\n");
			break;
			case 4:
				printf("nothing\n");
			break;
		}
		//puts(buf);
	}
	return 0;
}
