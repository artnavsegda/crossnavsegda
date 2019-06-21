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
	tcgetattr(fd,&tio);
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);

	write(fd,"\x01\x03\x01\x68\x00\x02\x44\x2B",8);
	//write(fd,"\xCA",1);
	//write(fd,"\xAF",1);
	//usleep(20*1000);

	/*bzero(frame,5);
	frame[0] = 0xB5;
	frame[1] = makecontrolbyte();
	frame[4] = makecontrolbyte();
	write(fd,frame,5);*/

	/*bzero(frame,4);
	frame[0] = makecontrolbyte();
	frame[3] = makecontrolbyte();
	write(fd,frame,4);*/

	/*bzero(frame,1);
	frame[0] = 0x01;
	sendcommand(fd,0xCA,frame,1);*/
	//write(fd,frame,1);
	//write(fd,genchecksum(frame,1),1);

	return 0;
}
