//art navsegda image format
#include <stdio.h>
#include <stdlib.h>
#include "artnavsegda.h"
#define WIDTH 10
#define HEIGHT 10
#define R 'r'
#define G 'g'
#define B 'b'

int main(int argc,char *argv[])
{
	if (argc < 6)
	{
		puts("format: command xsize ysize r g b");
		exit(1);
	}
	int x = 0;
	int y = 0;
	fputs(artnavsegda,stdout);
	fputc(atoi(argv[1]),stdout);
	fputc(atoi(argv[2]),stdout);
	while (x != atoi(argv[1]))
	{
		y = 0;
		while (y != atoi(argv[2]))
		{
			fputc(atoi(argv[3]),stdout);
			fputc(atoi(argv[4]),stdout);
			fputc(atoi(argv[5]),stdout);
			y++;
		}
		//fputs("SCANLINE",stdout);
		x++;
	}
	return 0;
}
