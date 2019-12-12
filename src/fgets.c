#include <stdio.h>

#define MAXLEN 1000

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		puts("enter filename");
		return 1;
	}

	FILE *script = fopen(argv[1],"r");

	if (script == NULL)
	{
		printf("cannot open %s\n",argv[1]);
		return 1;
	}

	char line[MAXLEN];

	while (fgets(line, MAXLEN, script))
	{
		printf("line: %s", line);
	}

	return 0;
}
