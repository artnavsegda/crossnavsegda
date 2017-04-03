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

char buf[100];
char ask[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x32, 0x03, 0x00, 0x00, 0x00, 0x01 };

tcpframestruct tcpframe = {
	.tsid = 1,
	.protoid = 0,
	.length = 6,
};

pduframestruct pduframe = {
	.unitid = 50,
	.fncode = 3,
};

mbframestruct mbframe = {
	.tsid = 0x0100,
	.protoid = 0x0000,
	.length = 0x0600,
	.pdu = {
		.unitid = 50
	}
};

mbframestruct askframe;

void printbinary(unsigned char value)
{
	for (int i = 0; i < 8; i++)
		printf("%u", (value >> (7-i)) & 0x01);
}

float gluefloat(short low, short high)
{
	float value;
	((short *)&value)[0] = low;
	((short *)&value)[1] = high;
	return value;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("name ip addr\n");
		return 1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}

	struct sockaddr_in client = {
		.sin_addr.s_addr = inet_addr(argv[1]),
		.sin_family = AF_INET,
		.sin_port = htons(502)
	};

	if (connect(sock,(struct sockaddr *)&client, sizeof(client)) == -1)
	{
		perror("connect error");
		close(sock);
		return 1;
	}

	mbframe.pdu.fncode = 4;
	mbframe.pdu.data.askreadregs.firstreg = htons(8);
	mbframe.pdu.data.askreadregs.regnumber = htons(24);

	ssize_t numwrite = send(sock,&mbframe,12,0);
	if (numwrite == -1)
	{
		perror("send error");
	}

	ssize_t numread = recv(sock,&askframe,6,0);
	if (numread == -1)
	{
		perror("recv error");
		close(sock);
		return 1;
	}

	numread = recv(sock,&askframe.pdu,ntohs(askframe.length),0);
	if (numread == -1)
	{
		perror("recv error");
		close(sock);
		return 1;
	}
	else
	{
		printf("%30s %f\n", "Elemental mercury:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[16]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[17])));
		printf("%30s %f\n", "Total mercury:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[2]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[3])));
		printf("%30s %f\n", "Oxidized mercury:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[4]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[5])));
		printf("%30s %f\n", "Monitor flow:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[6]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[7])));
		printf("%30s %f\n", "Vacuum:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[8]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[9])));
		printf("%30s %f\n", "Dilution pressure:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[10]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[11])));
		printf("%30s %f\n", "Bypass pressure:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[12]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[13])));
		printf("%30s %f\n", "Temperature of spectrometer:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[14]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[15])));
		printf("%30s %f\n", "Code of a current mode:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[0]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[1])));
		printf("%30s %f\n", "Errors and warnings:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[20]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[21])));
		printf("%30s %f\n", "Calibration coefficient:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[22]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[23])));
	//	printf("%30s %f\n", "PMT current:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[0]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[1])));
	//	printf("%30s %f\n", "PMT voltage:", gluefloat(ntohs(((short *)&askframe.pdu.data.reqread.bytes)[0]),ntohs(((short *)&askframe.pdu.data.reqread.bytes)[1])));
	}

	if (shutdown(sock, 2) == -1)
	{
		perror("shutdown error");
		close(sock);
		return 1;
	}

	close(sock);

	return 0;
}
