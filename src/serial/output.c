#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>

#define _BV(bit) (1 << (bit)) 

unsigned char genchecksum(unsigned char *massive, int sizeofmassive)
{
	unsigned char checksum = 0;
	for (int i=0;i<sizeofmassive;i++)
		checksum = checksum + massive[i];
	return checksum;
}

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

void sendcommand(int fd, unsigned char marker, unsigned char *frame, int framelength)
{
	unsigned char markerframe[1];
	markerframe[0] = marker;
	write(fd,markerframe,1);
	usleep(20*1000);
	write(fd,frame,framelength);
	markerframe[0] = genchecksum(frame,framelength);
	write(fd,markerframe,1);
	//write(fd,genchecksum(frame,framelength),1);
}

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
	if (argc != 3)
	{
		printf("name serial port and byte\n");
		exit(1);
	}
	fd = open(argv[1],O_RDWR | O_NOCTTY);
	if (fd == -1)
	{
		printf("error open serial port\n");
		exit(1);
	}
	//tcgetattr(fd,&tio);
	//tcflush(fd, TCIFLUSH);
	//tcsetattr(fd,TCSANOW,&tio);

	unsigned char controlbyte[1];
	sscanf(argv[2],"%X",&controlbyte[0]);
	write(fd,controlbyte,1);
	//write(fd,"\xAF",1);
	//write(fd,"\xCA",1);
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
