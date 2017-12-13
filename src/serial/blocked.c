#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
        
#define BAUDRATE B9600

int main(int argc, char *argv[])
{
        int fd,c, res;
        struct termios tio = {
		.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD,
		.c_iflag = IGNPAR,
		.c_oflag = 0,
		.c_lflag = 0,
		.c_cc[VTIME] = 1,
		.c_cc[VMIN] = 7
	};
        unsigned char buf[255];

	if (argc != 2)
	{
		printf("name serial port\n");
		exit(1);
	}
        
        fd = open(argv[1], O_RDWR | O_NOCTTY ); 
        if (fd  == -1)
	{
		perror("cannot open serial port");
		exit(1);
	}
        
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&tio);
        
        
        while (1)
	{       /* loop for input */
		res = read(fd,buf,255);   /* returns after 5 chars have been input */
		buf[res]=0;               /* so we can printf... */
		printf("%d:", res);
		for (int i = 0;i < res; i++)
			printf("0x%02X ",buf[i]);
		printf("\n");
        }
}
    
