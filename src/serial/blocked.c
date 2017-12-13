#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
        
#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

int main(int argc, char *argv[])
{
        int fd,c, res;
        struct termios oldtio,newtio;
        char buf[255];

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
        
        tcgetattr(fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
        newtio.c_iflag = IGNPAR;
        newtio.c_oflag = 0;
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = 0;
         
        newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */
        
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&newtio);
        
        
        while (1)
	{       /* loop for input */
		res = read(fd,buf,255);   /* returns after 5 chars have been input */
		buf[res]=0;               /* so we can printf... */
		printf("\n:%d:", res);
		for (int i = 0;i < res; i++)
			printf("0x%02X ",buf[i]);
        }
        tcsetattr(fd,TCSANOW,&oldtio);
}
    
