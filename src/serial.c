#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd;
	if (argc != 2)
	{
		printf("name serial port\n");
		exit(1);
	}
	fd = open(argv[1],O_RDWR | O_NOCTTY);
	if (fd == -1)
	{
		printf("error open serial port\n");
		exit(1);
	}
	return 0;
}
