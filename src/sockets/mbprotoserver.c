#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

unsigned short hrmassive[50];

unsigned char crmassive[20];

unsigned short generatecoils(int firstcoil, int numberofcoils)
{
	return crmassive[0]>>firstcoil;
}

unsigned char buf[100];

unsigned char data[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x32, 0x03, 0x02, 0x00, 0x00 };

struct tcpframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
};

struct askreadregstruct {
	unsigned short firstreg;
	unsigned short regnumber;
};

struct reqreadcoilsstruct {
	unsigned char bytestofollow;
	unsigned char coils[256];
};

struct reqreadwordstruct {
	unsigned char bytestofollow;
	unsigned short registers[127];
};

union pdudataunion {
	struct askreadregstruct askreadregs;
	struct reqreadcoilsstruct reqreadcoils;
	struct reqreadwordstruct reqreadholdings;
	unsigned short words[127];
	unsigned char bytes[254];
};

struct pduframestruct {
	unsigned char unitid;
	unsigned char fncode;
	union pdudataunion data;
//	unsigned short data[256];
};

struct mbframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
	struct pduframestruct pdu;
};

struct mbframestruct askmbframe, reqmbframe;

struct tcpframestruct tcpframe = {
	.tsid = 1,
	.protoid = 0,
	.length = 5,
};

struct pduframestruct pduframe = {
	.unitid = 50,
	.fncode = 3
};

struct tcpframestruct askframe;
struct pduframestruct askpduframe;

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

		//int numread = recv(msgsock,&askframe,6,0);
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
			//printf("TS id: %d\n", bswap_16(askframe.tsid));
			printf("TS id: %d\n", ntohs(askmbframe.tsid));
			//printf("Protocol id: %d\n", bswap_16(askframe.protoid));
			printf("Protocol id: %d\n", ntohs(askmbframe.protoid));
			//printf("Length: %d\n", bswap_16(askframe.length));
			printf("Length: %d\n", ntohs(askmbframe.length));
			/*for (int i=0; i<numread;i++)
			{
				printf("0x%02X ",buf[i]);
			}
			printf("\n");*/
		}

		//numread = recv(msgsock,&askpduframe,bswap_16(askframe.length),0);
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
			//printf("Unit id: %d\n", askpduframe.unitid);
			printf("Unit id: %d\n", askmbframe.pdu.unitid);
			//printf("Function code: %d\n", askpduframe.fncode);
			printf("Function code: %d\n", askmbframe.pdu.fncode);
			for (int i=0; i<(numread-2)/2;i++)
				printf("%u ",ntohs(askmbframe.pdu.data.words[i]));
				//printf("%u ",bswap_16(askpduframe.data[i]));
			printf("\n");
		}

		switch (askmbframe.pdu.fncode) {
			case 1:
			case 2:
				askmbframe.pdu.data.reqreadcoils.bytestofollow = ntohs(askmbframe.pdu.data.askreadregs.regnumber) / 8;
				if ((ntohs(askmbframe.pdu.data.askreadregs.regnumber) % 8)>0)
					askmbframe.pdu.data.reqreadcoils.bytestofollow++;
				askmbframe.length = htons(askmbframe.pdu.data.reqreadcoils.bytestofollow + 3);
			break;
			case 3:
			case 4:
				printf("numer of registers requested %d\n", ntohs(askmbframe.pdu.data.askreadregs.regnumber));
				askmbframe.pdu.data.reqreadholdings.bytestofollow = ntohs(askmbframe.pdu.data.askreadregs.regnumber) * 2;
				askmbframe.length = htons(askmbframe.pdu.data.reqreadholdings.bytestofollow + 3);
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

		shutdown(msgsock, 2);
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
		close(msgsock);
	}
	close(sock);

	return 0;
}
