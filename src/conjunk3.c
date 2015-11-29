#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char buf[100];
	//char test;
        FILE *sora;
        sora = fopen(argv[1],"rb");
        if (sora == NULL)
        {
                printf("fucking error");
                exit(0);
        }

	while (fread(buf,36,1,sora))
	{
		if (buf[0] == (char)0xf4)
			printf("%hhx start\n",buf[0]);

		printf("time is %hhx%hhx:%hhx%hhx:%hhx%hhx\n",buf[1]-0x30,buf[2]-0x30,buf[3]-0x30,buf[4]-0x30,buf[5]-0x30,buf[6]-0x30);

		if (buf[7] == (char)0xa5)
			printf("%hhx marker\n",buf[7]);
		printf("outgoing data %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx\n", buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15], buf[16], buf[17], buf[18], buf[19], buf[20], buf[21], buf[22], buf[23], buf[24], buf[25], buf[26], buf[27], buf[28], buf[29]);
		printf("first set is %hx\n",(unsigned short)buf[8]);
		if (buf[30] == (char)0xb5)
			printf("%hhx marker\n",buf[30]);
		//printf("incoming data 
		if (buf[35] == (char)0xf8)
			printf("%hhx stop\n",buf[35]);
		puts("read");
	}
		puts("read end");
	return 0;
}
