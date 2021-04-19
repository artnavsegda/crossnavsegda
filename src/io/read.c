#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define LENGTH 600000000

int main(void)
{
	//char buf[LENGTH];
	char *buf;
	int file;
	int number = 1;
	file = open("./chota2.txt", O_RDONLY);
	if (file == -1)
	{
		printf("error open\n");
		exit(1);
	}
	buf = (char *)malloc(LENGTH);
	while (number!=0)
	{
		if (number == -1)
		{
			printf("read error\n");
			exit(1);
		}
		number = read(file,buf,LENGTH);
		printf("read %d bytes\n", number);
	}
	return 0;
}
