#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("enter file name\n");
		return 1;
	}

	FILE * mystream = fopen(argv[1],"r");
	if (mystream == NULL)
	{
		perror("open file");
		return 1;
	}

	return 0;
}

