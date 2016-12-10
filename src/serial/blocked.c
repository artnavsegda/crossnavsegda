#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	unsigned char frame[1];
	int fd;
	struct termios tio = {
		.c_cflag = B9600 | CS8 | CLOCAL | CREAD,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = 0 
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

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);

	while (1)
	{
		if (read(fd,frame,1) == 1)
			printf("0x%X \n",frame[0]);
		else
			printf("empty\n");
	}

	return 0;
}
