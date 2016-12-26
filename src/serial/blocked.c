#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>

struct a5framestruct {
	short currentpmt;
	short valueamp1;
	short valueamp2;
	short valueamp3;
	short battery;
	short autosampler;
	short temperature;
	short currentbattery;
	char reserved1;
	char reserved2;
	char reserved3;
	char reserved4;
	char voltagepmt;
};

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

int readframe(int fd, int framelength, void *frame)
{
	unsigned char checksum[1];
	printf("read frame %d\n",read(fd,frame,framelength));
	printf("read checksum %d\n",read(fd,checksum,1));
	printf("checksum %x\n",checksum[0]);
	if (genchecksum(frame,framelength)==checksum[0])
	{
		printf("valid frame\n");
		/*for (int i=0;i<framelength;i++)
			printf("%02X ",frame[i]);
		printf("\n");*/
		return 0;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	unsigned char frame[22],checksum[1],confirm[1];
	unsigned char buf[100];
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
	printf("begin open\n");
	//fd = open(argv[1],O_RDWR | O_NOCTTY | O_NONBLOCK);
	//fd = open(argv[1],O_RDWR);
	//fd = open(argv[1],O_RDONLY);
	printf("open\n");

	if (fd == -1)
	{
		perror("error open serial port");
		exit(1);
	}
	else
		printf("serial port open\n");

	//fcntl(fd,F_SETFL,0);
	//tcgetattr(fd,&tio);
	//cfmakeraw(&tio);
	//tio.c_cc[VMIN] = 10;
	//tio.c_cc[VTIME] = 10;
	cfsetspeed(&tio,B9600);
	tcsetattr(fd,TCSANOW,&tio);

	//tcflush(fd, TCIFLUSH);
	//cfmakeraw(&tio);
	//fcntl(fd,F_SETFL,0);
	//tcsetattr(fd,TCSANOW,&tio);

	/*while (1)
	{
		printf("read %d\n", read(fd,frame,10));
	}*/

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
	int a5counter = 0;
	int afcounter = 0;
	struct a5framestruct a5frame;

	while(1)
	{
		if (read(fd,frame,1)==1)
		{
			printf("marker %X\n",frame[0]);
			switch (frame[0])
			{
				case 0xA5:
					/*printf("read a5 %d\n",read(fd,&a5frame,21));
					printf("read checksum %d\n",read(fd,checksum,1));
					printf("a5 checksum %x\n",checksum[0]);
					if (genchecksum((unsigned char *)&a5frame,21)==checksum[0])
						printf("valid frame\n");*/
					if (!readframe(fd,21,&a5frame))
					{
						printf("a5 counter %d\n",a5counter++);
						printf("%6d %6d %6d %6d %6d %6d %6d %6d\n",
								a5frame.currentpmt,
								a5frame.valueamp1,
								a5frame.valueamp2,
								a5frame.valueamp3,
								a5frame.battery,
								a5frame.autosampler,
								a5frame.temperature,
								a5frame.currentbattery);
					}
				break;
			//	case 0xAF:
					/*printf("read af %d\n",read(fd,frame,16));
					printf("read checksum %d\n",read(fd,checksum,1));
					printf("af checksum %x\n",checksum[0]);
					if (genchecksum(frame,16)==checksum[0])
						printf("valid frame\n");*/
			//		if (!readframe(fd,16))
			//			printf("af counter %d\n",afcounter++);
			//	break;
				/*case 0xAE:
					readframe(fd,8);
				break;
				case 0xA0:
					readframe(fd,4);
				break;
				case 0xA1:
					readframe(fd,25);
				break;
				case 0xAD:
					readframe(fd,4);
				break;
				case 0xAA:
					readframe(fd,2);
				break;
				case 0xA2:
					readframe(fd,2);
				break;
				case 0xA7:
					readframe(fd,1);
				break;
				case 0xA4:
					readframe(fd,4);
				break;
				case 0xA6:
					readframe(fd,4);
				break;
				case 0x75:
					readframe(fd,6);
				break;
				case 0x76:
					readframe(fd,2);
				break;
				case 0x77:
					readframe(fd,2);
				break;*/
				case 0xCA:
				case 0xBE:
				case 0xBD:
				case 0xBB:
				case 0xBA:
				case 0xBF:
				case 0xB0:
				case 0xB2:
				case 0xB6:
				case 0xB7:
				case 0xB4:
				case 0xC0:
				case 0xE3:
				case 0xE5:
				case 0xE6:
					read(fd,confirm,1);
					if (confirm[0] == frame[0])
						printf("valid %x conmfirmation\n",confirm[0]);
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
