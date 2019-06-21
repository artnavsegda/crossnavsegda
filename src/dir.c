#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>

int main(void)
{
	char path[MAXPATHLEN];
	getwd(path);
	printf("wd: %s\n",path);
	return 0;
}
