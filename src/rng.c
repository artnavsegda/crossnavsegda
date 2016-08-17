#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main()
{
	while (1)
		printf("%f\n",(float)rand()/(float)RAND_MAX);
	return 0;
}
