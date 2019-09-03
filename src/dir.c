#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <dirent.h>

int main(void)
{
	char path[MAXPATHLEN];
	getcwd(path,MAXPATHLEN);
	printf("wd: %s\n",path);
  DIR *d = opendir(path);
  struct dirent *dir;
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      puts(dir->d_name);
    }
    closedir(d);
  }
	return 0;
}
