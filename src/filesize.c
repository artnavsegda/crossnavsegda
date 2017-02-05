#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat filestat;
	if (argc != 2)
	{
		printf("enter filename\n");
		return 1;
	}
	if (stat(argv[1],&filestat) == -1)
	{
		perror(argv[1]);
		return 1;
	}

	printf("file size is %lld\n",filestat.st_size);

	return 0;
}

