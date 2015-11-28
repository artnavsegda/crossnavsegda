#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH  7000000

int open = 0;

//int m[20][9100000];
short *m[13];
short max[13];
short min[13];
short col[13];
int l;

int main(int argc, char *argv[])
{
	l = 0;
	FILE *sora;
	sora = fopen("./chota2.txt","r");
	if (sora == NULL)
	{
		printf("fucking error");
		exit(0);
	}
	else
		open = 1;
	memset(max,0,sizeof(max));
	memset(max,0,sizeof(min));
	for(int i=0;i<=12;i++)
	{
		m[i] = malloc(MAXLENGTH*sizeof(short));
	}
	while (fscanf(sora,"%hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd\n", &m[0][l],&m[1][l],&m[2][l],&m[3][l],&m[4][l],&m[5][l],&m[6][l],&m[7][l],&m[8][l],&m[9][l],&m[10][l],&m[11][l],&m[12][l])!=EOF)
	{
		for(int i=0;i<=12;i++)
		{
			if (min[i]==0) min[i]=m[i][l];
			if (max[i]==0) max[i]=m[i][l];
			if (m[i][l]<min[i]) min[i]=m[i][l];
			if (m[i][l]>max[i]) max[i]=m[i][l];
		}
		if (l >= MAXLENGTH)
			break;
		l++;
	}
	/*for(int i=1;i<=20;i++)
	{
		free(m[i]);
	}*/
	printf("length is %d\n",l);
	for(int i=0;i<=12;i++)
		printf("%d: min %d, max %d, span %d\n",i,min[i],max[i],max[i]-min[i]);
	fclose(sora);
	return 0;
}
