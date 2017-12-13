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

mbframestruct askmbframe, reqmbframe;

unsigned short table[100] = {0xABCD, 0xDEAD};
unsigned char bctable[100] = {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,0 , 0, 1 };
unsigned short amount = 100;

int main(int argc, char *argv[])
{
	struct termios tio = {
		.c_cflag = B9600 | CS8 | CLOCAL | CREAD,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = 0,
		.c_cc[VTIME] = 1,
		.c_cc[VMIN] = 7
	};

	int fd = open(argv[1], O_RDWR | O_NOCTTY );
	if (fd  == -1)
	{
		perror("cannot open serial port");
		exit(1);
	}

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);

	while(1)
	{
		int numread = read(fd,&askmbframe,255);
		if (numread == -1)
		{
			perror("recv error");
			close(fd);
			return 1;
		}
		else
		{
			printf("recv %d bytes\n",numread);
			printf("Unit id: %d\n", askmbframe.unitid);
			printf("Function code: %d\n", askmbframe.fncode);
			for (int i=0; i<((numread-2)/2)-1;i++)
				printf("%u ",ntohs(askmbframe.data.words[i]));
			printf("\n");
			printf("recieved CRC 0x%04X\n",askmbframe.data.words[((numread-2)/2)-1]);
			printf("calculated CRC 0x%04X\n",CRC16((char *)&askmbframe,numread-2));
		}

		int firstrequest = 0;
		int requestnumber = 0;
		int replylength;
		switch (askmbframe.fncode) {
			case 1:
			case 2:
				firstrequest = ntohs(askmbframe.data.askreadregs.firstreg);
				printf("Requesting bits starting from: %d\n", firstrequest);
				requestnumber = ntohs(askmbframe.data.askreadregs.regnumber);
				printf("Number of bits requested: %d\n", requestnumber);
				askmbframe.data.reqread.bytestofollow = requestnumber / 8;
				if ((requestnumber % 8)>0)
					askmbframe.data.reqread.bytestofollow++;
				replylength = askmbframe.data.reqread.bytestofollow + 3;
				// fill all requested coil bytes with zeroes
				for (int i = 0; i < askmbframe.data.reqread.bytestofollow;i++)
					askmbframe.data.reqread.bytes[i] = 0;
				// fill requested coil in bytes with bits
				for (int i = 0; i < requestnumber;i++)
					if (firstrequest+i < amount)
						if (bctable[firstrequest+i] != 0)
							askmbframe.data.reqread.bytes[i/8] = askmbframe.data.reqread.bytes[i/8] | (0x01 << i%8);
			break;
			case 3:
			case 4:
				firstrequest = ntohs(askmbframe.data.askreadregs.firstreg);
				printf("Requesing register starting from: %d\n", firstrequest);
				requestnumber = ntohs(askmbframe.data.askreadregs.regnumber);
				printf("Number of registers requested: %d\n", requestnumber);
				askmbframe.data.reqread.bytestofollow = requestnumber * 2;
				replylength = askmbframe.data.reqread.bytestofollow + 3;
				// fill every requested register with table values
				for (int i = 0; i < requestnumber;i++)
					if (firstrequest+i < amount)
						((unsigned short *)&askmbframe.data.reqread.bytes)[i] = htons(table[firstrequest+i]);
					else
						((unsigned short *)&askmbframe.data.reqread.bytes)[i] = htons(0x0000);
				/*for (int i = 0; i < requestnumber;i++)
					((unsigned short *)&askmbframe.pdu.data.reqread.bytes)[i] = htons(table[i]);*/
			break;
			case 5:
				if (ntohs(askmbframe.data.writereg.regaddress) < amount)
				{
					if (askmbframe.data.writereg.regvalue == 0)
						bctable[ntohs(askmbframe.data.writereg.regaddress)] = 0;
					else
						bctable[ntohs(askmbframe.data.writereg.regaddress)] = 1;
				}
				break;
			case 6:
				if (ntohs(askmbframe.data.writereg.regaddress) < amount)
					table[ntohs(askmbframe.data.writereg.regaddress)] = ntohs(askmbframe.data.writereg.regvalue);
				break;
			case 15:
				for (int i = 0; i<ntohs(askmbframe.data.writemultireg.regnumber);i++)
					if(ntohs(askmbframe.data.writemultireg.firstreg)+i < amount)
					{
						if (askmbframe.data.writereg.regvalue == 0)
							bctable[ntohs(askmbframe.data.writereg.regaddress)] = 0;
						else
							bctable[ntohs(askmbframe.data.writereg.regaddress)] = 1;
					}
				break;
				replylength = 9;
				break;
			case 16:
				for (int i = 0; i<ntohs(askmbframe.data.writemultireg.regnumber);i++)
					if(ntohs(askmbframe.data.writemultireg.firstreg)+i < amount)
						table[ntohs(askmbframe.data.writemultireg.firstreg)+i] = ntohs(askmbframe.data.writemultireg.registers[i]);
				replylength = 9;
				break;
			break;
		}

		printf("replylength %d\n",replylength+2);

		askmbframe.checksum = CRC16((char *)&askmbframe,replylength);

		printf("checksum %02X\n",askmbframe.checksum);

		int numwrite = write(fd,&askmbframe,replylength);
		if (numwrite == -1)
		{
			perror("send error");
			close(fd);
			return 1;
		}
		else
		{
			printf("send %d bytes ok\n",numwrite);
		}

		write(fd,&askmbframe.checksum,2);

		//shutdown(msgsock, 2);
		/*if (shutdown(msgsock, 2) == -1)
		{
			perror("shutdown error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("shutdown ok\n");
		}*/
		//close(msgsock);
	}
	close(fd);

	return 0;
}
