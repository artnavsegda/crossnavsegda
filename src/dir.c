#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>

int main(void)
{
	char path[MAXPATHLEN];
	getcwd(path,MAXPATHLEN);
	printf("wd: %s\n",path);
	return 0;
}
