#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <byteswap.h>

unsigned char buf[100];

unsigned char data[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x32, 0x03, 0x02, 0x00, 0x00 };

struct tcpframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
};

struct pduframestruct {
	unsigned char unitid;
	unsigned char fncode;
	unsigned short data[256];
};

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

		int numread = recv(msgsock,&askframe,6,0);
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
			printf("TS id: %d\n", bswap_16(askframe.tsid));
			printf("Protocol id: %d\n", bswap_16(askframe.protoid));
			printf("Length: %d\n", bswap_16(askframe.length));
			/*for (int i=0; i<numread;i++)
			{
				printf("0x%02X ",buf[i]);
			}
			printf("\n");*/
		}

		numread = recv(msgsock,&askpduframe,bswap_16(askframe.length),0);
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
			printf("Unit id: %d\n", askpduframe.unitid);
			printf("Function code: %d\n", askpduframe.fncode);
			for (int i=0; i<(numread-2)/2;i++)
				printf("%u ",bswap_16(askpduframe.data[i]));
			printf("\n");
		}

		switch (askpduframe.fncode) {
			case 1:
			case 2:
				// read coils/discrete inputs
				// data[0] = address of first coil/discrete
				// data[1] = number of colis to read
			case 3:
			case 4:
				// read holding/input registers
				// data[0] = address of first register
				// data[1] = number of registers to read
			case 5:
				// write coil
				// data[0] = address of coil
				// data[1] = value to write(0 = off, 0xFF00 for on)
			case 6:
				// write holding
				// data[0] = address of holding
				// data[1] = value of holding to write
			break;

		}

		int numwrite = send(msgsock,data,12,0);
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
