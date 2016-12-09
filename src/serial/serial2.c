#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>

#define _BV(bit) (1 << (bit)) 

struct req62struct {
	unsigned char sekunda;
	unsigned char minuta;
	unsigned char chas;
	unsigned char den;
	unsigned char myesats;
	unsigned char god;
	unsigned char flag;
	unsigned char nomer;
	unsigned short temp;
	unsigned short pressure;
	float concentration;
};

struct reqa7struct {
	int temnovoy_feu;
	int temnovoe_znacheniye_signala;
	int cal_a;
	int cal_b;
	short deltat;
	short norm_temp;
	short norm_press;
	short min_temp;
	short max_temp;
	short min_press;
	short max_press;
	int predel_norm;
	int predel_big;
	short const1opt;
	short const2opt;
	short const3opt;
	short const1cont;
	short const2cont;
	short regime;
	short dacmod;
	short sensfeu;
	short maxfeu;
	int mintokfeu;
	int reserve;
};

struct reqa5struct {
	int tokfeu;
	int znachsig;
	short tempgas;
	short pressgas;
	short tempcell;
	short voltagefeu;
	short voltagebatt;
	short reserve;
	unsigned char overload;
	unsigned char reserve2;
};

ssize_t readcs(int fd, void *buf, size_t count)
{
	ssize_t result = read(fd,buf,count);
	unsigned char checksum[1];
	read(fd,checksum,1);
	return result;
}

unsigned char genchecksum(unsigned char *buf, size_t count)
{
	unsigned char checksum = 0;
	for (int i=0;i<count;i++)
		checksum = checksum + buf[i];
	return checksum;
}

ssize_t writecs(int fd, const void *buf, size_t count)
{
	ssize_t result = write(fd,buf,count);
	unsigned char checksum[1];
	checksum[0] = genchecksum((unsigned char *)&buf,count);
	write(fd,checksum,1);
	return result;
}

int main(int argc, char *argv[])
{
	unsigned char control[1];
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

	while (read(fd,control,1))
	{
		write(fd,control,1);
		switch(control[0])
		{
			case 0x63:
				;
				unsigned int req63[2] = { 100, 100 };
				writecs(fd,req63,8);
			break;
			case 0x61:
				;
				unsigned int req61[1];
				read(fd,req61,4);
				printf("0x61 %u\n",req61[0]);
				write(fd,control,1);
			break;
			case 0x62:
				;
				char req62[240];
				writecs(fd,req62,240);
				/*for (int i=0;i<15)
				{
					struct req62struct req62;
					write(fd,req62,16);
				}*/
			break;
			case 0xBA:
				;
				char reqba[4];
				read(fd,reqba,4);
				printf("0xBA %s\n",reqba);
				write(fd,control,1);
			break;
			case 0xA0:
				;
				char reqa0[4] = "abcd";
				writecs(fd,reqa0,4);
			break;
			case 0x46:
				;
				char req46[1];
				read(fd,req46,1);
				printf("0x46 0x%X\n",req46[0]);
				write(fd,control,1);
			break;
			case 0xC6:
				;
				char reqc6[1];
				read(fd,reqc6,1);
				printf("0x46 0x%X\n",reqc6[0]);
				write(fd,control,1);
			break;
			case 0x47:
				;
				char req47[1] = { 0x01 };
				writecs(fd,req47,1);
			break;
			case 0xC7:
				;
				char reqc7[1] = { 0x00 };
				writecs(fd,reqc7,1);
			break;
			case 0x14:
				;
				char req14[2] = { 0x01, 0x02 };
				writecs(fd,req14,2);
			break;
			case 0x15:
				;
				char req15[2] = { 0x01, 0x02 };
				writecs(fd,req15,2);
			break;
			case 0x08:
				;
				unsigned int req08[1] = { 100 };
				writecs(fd,req08,4);
			break;
			case 0x09:
				;
			break;
			case 0xA7:
				;
				char reqa7[64];
				read(fd,reqa7,64);
				/* struct reqa7struct reqa7
				read(fd,&reqa7,64); */
				write(fd,control,1);
			break;
			case 0xA8:
				;
				char reqa8[64];
				writecs(fd,reqa7,64);
				/* struct reqa7struct reqa8
				writecs(fd,&reqa7,64); */
			break;
			case 0xC5:
				;
			break;
			case 0xC8:
				;
				char reqc8[1];
				read(fd,reqc8,1);
				printf("0xC8 0x%X\n",reqc8[0]);
				write(fd,control,1);
			break;
			case 0xC9:
				;
				char reqc9[1];
				read(fd,reqc9,1);
				printf("0xC9 0x%X\n",reqc9[0]);
				write(fd,control,1);
			break;
			case 0xCB:
				;
				char reqcb[1];
				read(fd,reqcb,1);
				printf("0xCB 0x%X\n",reqcb[0]);
				write(fd,control,1);
			break;
			case 0xA9:
				;
				char reqa9[1];
				read(fd,reqa9,1);
				printf("0xA9 0x%X\n",reqa9[0]);
				write(fd,control,1);
			break;
			case 0xAA:
				;
				char reqaa[1];
				read(fd,reqaa,1);
				printf("0xAA 0x%X\n",reqaa[0]);
				write(fd,control,1);
			break;
			case 0xAC:
				;
				char reqac[1];
				read(fd,reqac,1);
				printf("0xAC 0x%X\n",reqac[0]);
				write(fd,control,1);
			break;
			case 0xC1:
				;
				char reqc1[1];
				read(fd,reqc1,1);
				printf("0xC1 0x%X\n",reqc1[0]);
				write(fd,control,1);
			break;
			case 0xC2:
				;
				char reqc2[1];
				read(fd,reqc2,1);
				printf("0xC2 0x%X\n",reqc2[0]);
				write(fd,control,1);
			break;
			case 0xCA:
				;
				char reqca[1];
				read(fd,reqca,1);
				printf("0xCA 0x%X\n",reqca[0]);
				write(fd,control,1);
			break;
			case 0xA5:
				;
				write(fd,"\xA5",1);
				struct reqa5struct reqa5;
				writecs(fd,&reqa5,22);
			break;
			default:
			break;
		}
		//unsigned char sum[1];
		//read(fd,sum,1);
	}

	//write(fd,frame,5);

	return 0;
}
