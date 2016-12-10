//art navsegda image format
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "artnavsegda.h"

int main()
{
	char r,g,b;
	int x = 0;
	int y = 0;
	int width;
	int height;
	int magiclength = strlen(artnavsegda);
	char magic[sizeof(artnavsegda)];
	fgets(magic,magiclength+1,stdin);
	if (strcmp(artnavsegda,magic)!=0)
	{
		printf("incorrect format\n");
		exit(1);
	}

	width = fgetc(stdin);
	printf("width %d\n",width);
	height = fgetc(stdin);
	printf("height %d\n",height);

	while (x != width)
	{
		y = 0;
		while (y != height)
		{
			r = fgetc(stdin);
			fputc(r,stdout);
			g = fgetc(stdin);
			fputc(g,stdout);
			b = fgetc(stdin);
			fputc(b,stdout);
			y++;
		}
		fputs("SCANLINE",stdout);
		x++;
	}
	return 0;
}
