#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>

struct kalibrstruct {
	unsigned char marker;
	unsigned char coefficentamp3;
	unsigned char coefficentamp2;
	unsigned char coefficentamp1;
	short dark_current;
	short biasamp3;
	short biasamp2;
	short biasamp1;
	short switch_threshhold;
	short coefficentcalib;
	unsigned char zerobias;
	unsigned char checksum;
};

struct kalibrstruct kalibr;

unsigned char genchecksum(unsigned char *massive, int sizeofmassive)
{
	unsigned char checksum = 0;
	for (int i=0;i<sizeofmassive;i++)
		checksum = checksum + massive[i];
	return checksum;
}

void sendcommand(int fd, unsigned char marker, unsigned char *frame, int framelength)
{
	unsigned char markerframe[1];
	unsigned char checksum[1];
	markerframe[0] = marker;
	write(fd,markerframe,1);
	usleep(20*1000);
	write(fd,frame,framelength);
	checksum[0] = genchecksum(frame,framelength);
	write(fd,checksum,1);
}

void transfermode(int fd)
{
	unsigned char frame[1];
	bzero(frame,1);
	frame[0] = 0x01;
	sendcommand(fd,0xCA,frame,1);
}

int main(int argc, char *argv[])
{
	unsigned char frame[22],checksum[1];
	unsigned char buf[100];
	int fd;
	struct termios tio = {
		.c_cflag = B9600 | CS8 | CLOCAL | CREAD,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = 0,
	       	.c_cc[VTIME] = 100,
		.c_cc[VMIN] = 100
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

	tcflush(fd, TCIFLUSH);
//	cfmakeraw(&tio);
	tcsetattr(fd,TCSANOW,&tio);

	int counter=0;
	/*bzero(frame,1);
	frame[0] = 0x01;
	sendcommand(fd,0xCA,frame,1);*/
	//transfermode(fd);

	printf("start\n");
	while (1)
	{
		//printf("try read\n");
		if (read(fd,frame,1) == 1)
		{
		//	printf("read %X\n",frame[0]);
			if (frame[0] != 0xA5)
			{
				counter++;
			}
			else
			{
				printf("a5 length %d\n", counter);
				if (counter == 20)
					transfermode(fd);
				if (counter == 22)
					break;
				counter = 0;
			}
		}
	}

	printf("read %d\n",read(fd,frame,22));

	while(1)
	{
		printf("read %d\n",read(fd,frame,1));
		//printf("marker %X\n",frame[0]);
		switch (frame[0])
		{
			case 0xA5:
				printf("read a5 %d\n",read(fd,frame,21));
				printf("read checksum %d\n",read(fd,checksum,1));
				if (genchecksum(frame,21)==checksum[0])
					printf("valid frame\n");
			break;
			default:
				break;
		}
		/*if (frame[0] == 0xA5)
		{
			printf("read a5 %d\n",read(fd,frame,21));
			printf("read checksum %d\n",read(fd,checksum,1));
			if (genchecksum(frame,21)==checksum[0])
				printf("valid frame\n");
			//printf("calculate checksum %x\n",genchecksum(frame,21));
			//printf("checksum %x\n",frame[0]);
		}*/
	}

	//printf("marker %X\n",frame[0]);


	/*while (frame[0] != 0xA5)
		read(fd,frame,1);*/

	//printf("2 read %d\n", read(fd, buf, 100));
	
	//printf("3 read %d\n", read(fd, checksum, 1));

	//printf("recieved checksum: %x\n", checksum[0]);
	//printf("calculated checksum: %d\n", genchecksum((unsigned char *)&buf, 21));

	/*write(fd, "\xAF" ,1);
	//tcflush(fd, TCIFLUSH);

	//read(fd, &kalibr, 18);
	int numread = read(fd, buf, 18);

	printf("1 read %d data\n", numread);

	usleep(20*1000);

	numread = read(fd, buf, 18);

	printf("2 read %d data\n", numread);

	usleep(20*1000);

	numread = read(fd, buf, 18);

	printf("3 read %d data\n", numread);

	//printf("recieved checksum: %x\n", buf[0]);
	//printf("calculated checksum: %d\n", genchecksum((unsigned char *)&kalibr, 18));

	//read(fd, buf, 10);*/

	/*while (1)
	{
		if (read(fd,frame,1) == 1)
			printf("0x%X \n",frame[0]);
		else
			printf("empty\n");
	}

	printf("success\n");*/

	return 0;
}
