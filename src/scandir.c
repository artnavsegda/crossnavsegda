#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <dirent.h>

int main(void)
{
  struct dirent **dirs;

  int n = scandir("./",&dirs,NULL,alphasort);
  if (n >= 0)
  {
    for (int cnt = 0;cnt < n;++cnt)
      puts(dirs[cnt]->d_name);
  }
  else
    perror("Cannot open directory");

	return 0;
}
