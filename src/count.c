#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int count = 0;
	int numbers;
	int a, b, c, d, e, f, g, h, i, j, k, l, m;
	int am, bm, cm, dm, em, fm, gm, hm, im, jm, km, lm, mm;
	am=0;bm=0;cm=0;dm=0;em=0;fm=0;gm=0;hm=0;im=0;jm=0;km=0;lm=0;mm=0;
	if (argc == 1)
	{
		printf("please set num number\n");
		exit(1);
	}
	numbers = atoi(argv[1]);
	while (scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d\n", &a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,&m)!=EOF)
	{
		count++;
		am += a;
		bm += b;
		cm += c;
		dm += d;
		em += e;
		fm += f;
		gm += g;
		hm += h;
		im += i;
		jm += j;
		km += k;
		lm += l;
		mm += m;
		if (count == numbers)
		{
			printf("%d %d %d %d %d %d %d %d %d %d %d %d %d\n",am/numbers, bm/numbers, cm/numbers, dm/numbers, em/numbers, fm/numbers, gm/numbers, hm/numbers, im/numbers, jm/numbers, km/numbers, lm/numbers, mm/numbers);
			count = 0;
			am=0;bm=0;cm=0;dm=0;em=0;fm=0;gm=0;hm=0;im=0;jm=0;km=0;lm=0;mm=0;
		}
	}
	return 0;
}
