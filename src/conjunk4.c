#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned char buf[100];
	short sbuf[100];
	//char test;
        FILE *sora;
        sora = fopen(argv[1],"rb");
        if (sora == NULL)
        {
                printf("fucking error");
                exit(0);
        }

	while (1)
	{
		fread(buf,1,1,sora);
		if (buf[0] == 0xf4)
		{
		//	printf("%hhx start\n",buf[0]);
		}
		else
			break;

		fread(buf,6,1,sora);
		if (buf[0] >= 0x30)
			buf[0] -= 0x10;
		if (buf[1] >= 0x30)
			buf[1] -= 0x10;
		printf("%hhu%hhu:%hhu%hhu:%hhu%hhu ",buf[0]-0x20,buf[1]-0x20,buf[2]-0x30,buf[3]-0x30,buf[4]-0x30,buf[5]-0x30);

		fread(buf,1,1,sora);
		if (buf[0] == 0xa5)
		{
		//	printf("%hhx marker\n",buf[0]);
		}
		else
			break;
		//fread(buf,22,1,sora);
		//printf("outgoing data %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15], buf[16], buf[17], buf[18], buf[19], buf[20], buf[21]);
		fread(sbuf,20,1,sora);
		//printf(" %hhu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu %hu\n", (char)0xa5, sbuf[0], sbuf[1], sbuf[2], sbuf[3], sbuf[4], sbuf[5], sbuf[6], sbuf[7], sbuf[8], sbuf[9], sbuf[10]);
		fread(buf,3,1,sora);
		if (buf[2] == 0xb5)
		{
		//	printf("%hhx marker\n",buf[0]);
		}
		else
			break;
		printf("%hhu %hu %hu %hu %hd %hu %hu %hu %hu %hu %hu %hu %hhu %hhu\n", (char)0xa5, sbuf[0], sbuf[1], sbuf[2], sbuf[3], sbuf[4], sbuf[5], sbuf[6], sbuf[7], sbuf[8], sbuf[9], sbuf[10], buf[0], buf[1]);
		fread(buf,4,1,sora);
		//printf("incoming data %hhx %hhx %hhx %hhx\n",   buf[0], buf[1], buf[2], buf[3]);
		fread(buf,1,1,sora);
		if (buf[0] == 0xf8)
		{
		//	printf("%hhx stop\n",buf[0]);
		}
		else
			break;
		//puts("read");
	}
		//puts("read end");
	return 0;
}
