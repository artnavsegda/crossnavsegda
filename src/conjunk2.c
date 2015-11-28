#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char buf[100];
	char test;
	int file;
	file = open("./chota2.bin", O_RDONLY);
	if (file == -1)
	{
		printf("error open\n");
		exit(1);
	}
	while (read(file,buf,36)==36)
	{
		//if (buf[0] == (char)0xf4)
		//	printf("%hhx start\n",buf[0]);

		printf("%hhx %hhx %hhx %hhx %hhx %hhx\n",buf[1],buf[2],buf[3],buf[4],buf[5],buf[6]);

		//if (buf[7] == (char)0xa5)
		//	printf("%hhx marker\n",buf[7]);
		//if (buf[35] == (char)0xf8)
		//	printf("%hhx stop\n",buf[35]);
		//puts("read");
	}
		puts("read end");
	return 0;
}
