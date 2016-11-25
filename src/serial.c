#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, char *argv[])
{
	int fd;
	struct termios tio = {
		.c_cflag = B9600,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = ICANON
	};
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
	//tcgetattr(fd,&tio);
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);
	return 0;
}
