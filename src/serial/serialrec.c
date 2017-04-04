#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char *argv[])
{
	unsigned char frame[22];
	int fd;
	//struct termios tio;
	struct termios tio = {
		.c_cflag = B9600 | CS8 | CLOCAL | CREAD,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = 0,
	       	.c_cc[VTIME] = 100,
		.c_cc[VMIN] = 22
	};

	if (argc != 2)
	{
		printf("name serial port\n");
		exit(1);
	}

	fd = open(argv[1],O_RDWR | O_NOCTTY);

	if (fd == -1)
	{
		perror("error open serial port");
		exit(1);
	}
	else
		printf("serial port open\n");

	cfsetspeed(&tio,B9600);
	tcsetattr(fd,TCSANOW,&tio);

	while (1)
	{
		if (read(fd,frame,1) == 1)
			write(STDOUT_FILENO,frame,1);
	}

	return 0;
}
