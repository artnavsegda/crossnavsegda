#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/time.h>

char buf[1000];

int sock;

void process(unsigned char *message, int numread)
{
	int numwrite = 0;
	int index = 0;
	printf("recv %d bytes: ",numread);
	for (int i=0; i<numread;i++)
	{
		printf("0x%02X ",message[i]);
	}
	printf("\n");

	while (index < numread)
	{
		unsigned char *buf = &message[index];

		printf("payload type 0x%02X, ",buf[0]);

		int payloadLength = buf[2];
		printf("payload length %d: ",payloadLength);

		unsigned char * payload = &buf[3];

		for (int i=0; i<payloadLength;i++)
		{
			printf("0x%02X ",payload[i]);
		}
		
		switch (buf[0])
		{
			case 0x0f:
				printf("Client registration request");
				numwrite = send(sock, "\x01\x00\x0b\x00\x00\x00\x00\x00" "\x03" "\x40\xff\xff\xf1\x01", 14, 0);
			case 0x02:
				printf("registration result");
				if (payloadLength == 4 && (memcmp(payload,"\x00\x00\x00\x1f",4) == 0))
				{
					puts("registration ok");
					numwrite = send(sock, "\x05\x00\x05\x00\x00\x02\x03\x00", 8, 0);
				}
			break;
			case 0x05:
				printf("data\n");
				printf("datatype 0x%02X ", payload[3]);
				switch (payload[3])
				{
					case 0x00:
						printf("digital join %d state %d", (((payload[5] & 0x7F) << 8) | payload[4]) + 1, ((payload[5] & 0x80) >> 7) ^ 0x01);
					break;
					case 0x14:
						printf("analog join %d value %d", ((payload[4] << 8) | payload[5]) + 1, (payload[6] << 8) + payload[7]);
					break;
					case 0x03:
						printf("update request type 0x%02X ", payload[4]);
						switch (payload[4])
						{
							case 0x00:
								printf("standard update request");
							break;
							case 0x16:
								printf("mysterious penultimate update-response");
							break;
							case 0x1C:
								printf("end-of-query");
								numwrite = send(sock, "\x05\x00\x05\x00\x00\x02\x03\x1d", 8, 0);
								numwrite += send(sock, "\x0D\x00\x02\x00\x00", 5, 0);
							break;
							case 0x1D:
								printf("end-of-query acknowledgement");
							break;
						}
					break;
				}
			break;
			case 0x0D:
			case 0x0E:
				printf("heartbeat");
			default:
			break;
		}

		printf("\n");

		if (numwrite > 0)
			printf("%d bytes sent\n", numwrite);

		index = index+payloadLength+3;
	}
}

void timer_handler(int signal)
{
	int numwrite = 0;
	//printf("alarm\n");
	numwrite = send(sock, "\x0D\x00\x02\x00\x00", 5, 0);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		puts("usage: cipcontrol <ipaddr>");
		return 0;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
	{
		printf("socket ok\n");
	}
	struct sockaddr_in client = {
		.sin_addr.s_addr = inet_addr(argv[1]),
		.sin_family = AF_INET,
		.sin_port = htons(41794)
	};
	if (connect(sock,(struct sockaddr *)&client, sizeof(client)) == -1)
	{
		perror("connect error");
		close(sock);
		return 1;
	}
	else
	{
		printf("connect ok\n");
	}

	struct itimerval it_val;
	signal(SIGALRM, timer_handler);
	it_val.it_value.tv_sec = 5;
	it_val.it_value.tv_usec = 0;
	it_val.it_interval = it_val.it_value;
	setitimer(ITIMER_REAL, &it_val, NULL);

	int numread = 0;
	do {
		numread = recv(sock,buf,1000,0);
		process(buf,numread);
	} while (numread > 0);

       	if (numread == -1)
	{
		perror("recv error");
	}
	else
	{
		printf("recv %d bytes ok\n");
	}

	shutdown(sock, 2);
	close(sock);

	return 0;
}

