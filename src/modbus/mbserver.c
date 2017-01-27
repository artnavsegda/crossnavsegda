#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "modbus.h"

struct mbframestruct askmbframe, reqmbframe;

unsigned short table[100] = {0xABCD, 0xDEAD};
unsigned char bctable[100];
unsigned short amount = 100;

int main()
{
	int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
	{
		printf("socket ok\n");
	}
	int optval = 1;
	setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port = htons(1100)
	};

	if (bind(sock,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		perror("bind error");
		close(sock);
		return 1;
	}
	else
	{
		printf("bind ok\n");
	}

	if (listen(sock,10) == -1)
	{
		perror("listen error");
		close(sock);
		return 1;
	}
	else
	{
		printf("listen ok\n");
	}

	while(1)
	{
		int msgsock = accept(sock,NULL,NULL);
		if (msgsock == -1)
		{
			perror("accept error");
			close(sock);
			return 1;
		}
		else
		{
			printf("accept ok\n");
		}

		int numread = recv(msgsock,&askmbframe,6,0);
		if (numread == -1)
		{
			perror("recv error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("recv %d bytes\n",numread);
			printf("TS id: %d\n", ntohs(askmbframe.tsid));
			printf("Protocol id: %d\n", ntohs(askmbframe.protoid));
			printf("Length: %d\n", ntohs(askmbframe.length));
		}

		numread = recv(msgsock,&askmbframe.pdu,ntohs(askmbframe.length),0);
		if (numread == -1)
		{
			perror("recv error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("recv %d bytes\n",numread);
			printf("Unit id: %d\n", askmbframe.pdu.unitid);
			printf("Function code: %d\n", askmbframe.pdu.fncode);
			for (int i=0; i<(numread-2)/2;i++)
				printf("%u ",ntohs(askmbframe.pdu.data.words[i]));
			printf("\n");
		}

		int firstrequest = 0;
		int requestnumber = 0;
		switch (askmbframe.pdu.fncode) {
			case 1:
			case 2:
				firstrequest = ntohs(askmbframe.pdu.data.askreadregs.firstreg);
				printf("Requesting bits starting from: %d\n", firstrequest);
				requestnumber = ntohs(askmbframe.pdu.data.askreadregs.regnumber);
				printf("Number of bits requested: %d\n", requestnumber);
				askmbframe.pdu.data.reqread.bytestofollow = requestnumber / 8;
				if ((requestnumber % 8)>0)
					askmbframe.pdu.data.reqread.bytestofollow++;
				askmbframe.length = htons(askmbframe.pdu.data.reqread.bytestofollow + 3);
				// fill all requested coil bytes with zeroes
				for (int i = 0; i < requestnumber;i++)
					if (bctable[firstrequest+i] != 0)
						askmbframe.pdu.data.reqread.bytes[i/8] = askmbframe.pdu.data.reqread.bytes[i/8] & (0x80 >> i%8);
					else
						askmbframe.pdu.data.reqread.bytes[i/8] = askmbframe.pdu.data.reqread.bytes[i/8] | ~(0x80 >> i%8);
			break;
			case 3:
			case 4:
				firstrequest = ntohs(askmbframe.pdu.data.askreadregs.firstreg);
				printf("Requesing register starting from: %d\n", firstrequest);
				requestnumber = ntohs(askmbframe.pdu.data.askreadregs.regnumber);
				printf("Number of registers requested: %d\n", requestnumber);
				askmbframe.pdu.data.reqread.bytestofollow = requestnumber * 2;
				askmbframe.length = htons(askmbframe.pdu.data.reqread.bytestofollow + 3);
				// fill every requested register with table values
				for (int i = 0; i < requestnumber;i++)
					if (firstrequest+i < amount)
						((unsigned short *)&askmbframe.pdu.data.reqread.bytes)[i] = htons(table[firstrequest+i]);
					else
						((unsigned short *)&askmbframe.pdu.data.reqread.bytes)[i] = htons(0x0000);
				/*for (int i = 0; i < requestnumber;i++)
					((unsigned short *)&askmbframe.pdu.data.reqread.bytes)[i] = htons(table[i]);*/
			break;
			case 5:
				if (ntohs(askmbframe.pdu.data.writereg.regaddress) < amount)
				{	
					if (askmbframe.pdu.data.writereg.regvalue == 0)
						bctable[ntohs(askmbframe.pdu.data.writereg.regaddress)] = 0;
					else
						bctable[ntohs(askmbframe.pdu.data.writereg.regaddress)] = 1;
				}	
				break;
			case 6:
				if (ntohs(askmbframe.pdu.data.writereg.regaddress) < amount)
					table[ntohs(askmbframe.pdu.data.writereg.regaddress)] = ntohs(askmbframe.pdu.data.writereg.regvalue);
				break;
			case 15:
				for (int i = 0; i<ntohs(askmbframe.pdu.data.writemultireg.regnumber);i++)
					if(ntohs(askmbframe.pdu.data.writemultireg.firstreg)+i < amount)
					{	
						if (askmbframe.pdu.data.writereg.regvalue == 0)
							bctable[ntohs(askmbframe.pdu.data.writereg.regaddress)] = 0;
						else
							bctable[ntohs(askmbframe.pdu.data.writereg.regaddress)] = 1;
					}	
				break;
				askmbframe.length = htons(6);
				break;
			case 16:
				for (int i = 0; i<ntohs(askmbframe.pdu.data.writemultireg.regnumber);i++)
					if(ntohs(askmbframe.pdu.data.writemultireg.firstreg)+i < amount)
						table[ntohs(askmbframe.pdu.data.writemultireg.firstreg)+i] = ntohs(askmbframe.pdu.data.writemultireg.registers[i]);
				askmbframe.length = htons(6);
				break;
			break;
		}

		int replylength = ntohs(askmbframe.length) + 6;
		printf("replylength %d\n",replylength);

		int numwrite = send(msgsock,&askmbframe,replylength,0);
		if (numwrite == -1)
		{
			perror("send error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("send %d bytes ok\n",numwrite);
		}

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
	close(sock);

	return 0;
}
