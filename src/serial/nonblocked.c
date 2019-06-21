#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	unsigned char frame[100];
	int fd, ret;
	struct termios tio = {
		.c_cflag = B9600 | CS8 | CLOCAL | CREAD,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = 0,
		.c_cc[VMIN] = 0,
		.c_cc[VTIME] = 100
	};

	if (argc != 2)
	{
		printf("name serial port\n");
		exit(1);
	}

	fd = open(argv[1],O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd == -1)
	{
		printf("error open serial port\n");
		exit(1);
	}

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);

	while (1)
	{
		ret = read(fd,frame,100);
		if (ret > 0)
		{
			printf("ret %d, read 0x%02X\n",ret,frame[0]);
		}
	}

	return 0;
}
