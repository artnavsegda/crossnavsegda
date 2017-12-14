#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "modbus.h"

unsigned short CRC16 (const unsigned char *nData, unsigned short wLength);

char buf[100];
char ask[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x32, 0x03, 0x00, 0x00, 0x00, 0x01 };

mbframestruct mbframe = {
	.unitid = 50
};

mbframestruct askframe;

void printbinary(unsigned char value)
{
	for (int i = 0; i < 8; i++)
		printf("%u", (value >> (7-i)) & 0x01);
}

int main(int argc, char *argv[])
{
        struct termios tio = {
                .c_cflag = B9600 | CS8 | CLOCAL | CREAD,
                .c_iflag = IGNPAR,
                .c_oflag = 0,
                .c_lflag = 0,
                .c_cc[VTIME] = 1,
                .c_cc[VMIN] = 50
        };

	if (argc < 4)
	{
		printf("name serial port device id function code and its values\n");
		printf("1 first amount: read coil\n");
		printf("2 first amount: read discrete\n");
		printf("3 first amount: read holding\n");
		printf("4 first amount: read input\n");
		printf("5 number value: write coil\n");
		printf("6 number value: write holding\n");
		printf("15 first amount number value: write miltiple coil\n");
		printf("16 first amount number value: write miltiple holding\n");
		return 1;
	}

	sscanf(argv[2],"%hhu",&mbframe.unitid); // <-----
	sscanf(argv[3],"%hhu",&mbframe.fncode); // <-----

	switch (mbframe.fncode)
	{
		case 1:
		case 2:
			if (argc < 6)
			{
				printf("name first coil/discrete and amount to return\n");
				return 1;
			}
			sscanf(argv[4],"%hu",&mbframe.data.askreadregs.firstreg);
			mbframe.data.askreadregs.firstreg = htons(mbframe.data.askreadregs.firstreg);
			sscanf(argv[5],"%hu",&mbframe.data.askreadregs.regnumber);
			mbframe.data.askreadregs.regnumber = htons(mbframe.data.askreadregs.regnumber);
			break;
		case 3:
		case 4:
			if (argc < 6)
			{
				printf("name first input/holding and amount to return\n");
				return 1;
			}
			sscanf(argv[4],"%hu",&mbframe.data.askreadregs.firstreg);
			mbframe.data.askreadregs.firstreg = htons(mbframe.data.askreadregs.firstreg);
			sscanf(argv[5],"%hu",&mbframe.data.askreadregs.regnumber);
			mbframe.data.askreadregs.regnumber = htons(mbframe.data.askreadregs.regnumber);
			break;
		case 5:
		case 6:
			if (argc < 6)
			{
				printf("name register number and value to set\n");
				return 1;
			}
			sscanf(argv[4],"%hu",&mbframe.data.writereg.regaddress);
			mbframe.data.writereg.regaddress = htons(mbframe.data.writereg.regaddress);
			sscanf(argv[5],"%hu",&mbframe.data.writereg.regvalue);
			mbframe.data.writereg.regvalue = htons(mbframe.data.writereg.regvalue);
			break;
		case 15:
		case 16:
			if (argc < 7)
			{
				printf("name first register, registers amount to set, number of bytes to follow and bytes with values\n");
				return 1;
			}
			sscanf(argv[4],"%hu",&mbframe.data.writemulticoil.firstreg);
			mbframe.data.writemulticoil.firstreg = htons(mbframe.data.writemulticoil.firstreg);
			sscanf(argv[5],"%hu",&mbframe.data.writemulticoil.regnumber);
			mbframe.data.writemulticoil.regnumber = htons(mbframe.data.writemulticoil.regnumber);
			sscanf(argv[6],"%hhu",&mbframe.data.writemulticoil.bytestofollow);
			for (int i=0;i<mbframe.data.writemulticoil.bytestofollow;i++)
				sscanf(argv[5+i],"%hhu",&mbframe.data.writemulticoil.coils[i]);
			break;
		default:
			printf("unknown function number");
			return 1;
			break;
	}

        int fd = open(argv[1], O_RDWR | O_NOCTTY );
        if (fd  == -1)
        {
                perror("cannot open serial port");
                exit(1);
        }

        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&tio);

	mbframe.checksum = CRC16((unsigned char *)&mbframe,6);

	printf("checksum %02X\n",mbframe.checksum);

	ssize_t numwrite = write(fd,&mbframe,6);
	if (numwrite == -1)
	{
		perror("send error");
	}
	else
	{
		printf("send %zd bytes ok\n", numwrite);
	}

	write(fd,&mbframe.checksum,2);

	int numread = read(fd,&askframe,255);
	if (numread == -1)
	{
		perror("recv error");
		close(fd);
		return 1;
	}
	else
	{
		printf("recv %zd bytes\n",numread);
		printf("Unit id: %d\n", askframe.unitid);
		printf("Function code: %d\n", askframe.fncode);
		for (int i=0; i<numread;i++)
			printf("0x%02hhX ",((char *)&askframe)[i]);
		printf("\n");
		switch(askframe.fncode)
		{
		case 1:
		case 2:
			printf("number of bytes containing bit values: %d\n",askframe.data.reqread.bytestofollow);
			for (int i=0;i<askframe.data.reqread.bytestofollow;i++)
			{
				printf("0x%02hhX(",askframe.data.reqread.bytes[i]);
				printbinary(askframe.data.reqread.bytes[i]);
				printf(") ");
			}
			printf("\n");
		break;
		case 3:
		case 4:
			printf("number of registers: %d\n",askframe.data.reqread.bytestofollow/2);
			for (int i=0;i<askframe.data.reqread.bytestofollow/2;i++)
			{
				printf("0x%04hX ",((short *)&askframe.data.reqread.bytes)[i]);
			}
			printf("\n");
		break;
		case 5:
		case 6:
			printf("register number %u\n", ntohs(askframe.data.writereg.regaddress));
			printf("register value %u\n", ntohs(askframe.data.writereg.regvalue));
		break;
		case 15:
		case 16:
			printf("first register %u\n", ntohs(askframe.data.writemulticoil.firstreg));
			printf("registers amount %u\n", ntohs(askframe.data.writemulticoil.regnumber));
		break;
		default:
			printf("unknown function number");
		break;
		}
		printf("recieved CRC 0x%04hX\n",((short *)&askframe.data.reqread.bytes)[1+((numread-6))/2]);
		printf("calculated CRC 0x%04hX\n",CRC16((unsigned char *)&askframe,numread-2));
	}

	close(fd);

	return 0;
}
