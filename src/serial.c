#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>

#define _BV(bit) (1 << (bit)) 

unsigned char makecontrolbyte(void)
{
	unsigned char controlbyte = 0;
	controlbyte |= _BV(1); //ign
	controlbyte |= _BV(2); //zero
	controlbyte |= _BV(3); //cell
	controlbyte |= _BV(4); //cal
	controlbyte |= _BV(5); //total
	return controlbyte;
}

int main(int argc, char *argv[])
{
	unsigned char frame[5];
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
	//tcgetattr(fd,&tio);
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);

	bzero(frame,5);
	frame[0] = 0xB5;
	frame[1] = makecontrolbyte();
	frame[4] = makecontrolbyte();

	write(fd,frame,5);

	return 0;
}
