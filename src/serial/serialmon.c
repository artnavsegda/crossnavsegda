#include <stdio.h>

struct dataunit {
	unsigned char rxnum;
	unsigned char recbyte;
	unsigned long millis;
};

struct dataunit datamassive[10000];

int main(void)
{
	int position = 0;
	while (scanf("%lu:RX%hhu:%hhX",&datamassive[position].millis,&datamassive[position].rxnum,&datamassive[position].recbyte) != EOF)
		position++;
	printf("%d record read\n",position);
	for (int i=0; i<position; i++)
		printf("%lu:RX%hhu:%hhX\n", datamassive[i].millis,datamassive[i].rxnum,datamassive[i].recbyte);
	return 0;
}
