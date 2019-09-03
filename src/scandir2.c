#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <dirent.h>
#include <string.h>

static int fileselect(const struct dirent *entry)
{
  char *ptr = rindex(entry->d_name, '.');
  if ((ptr!=NULL) && ((strcmp(ptr,".c")==0)))
    return 1;
  else
    return 0;
}

int main(void)
{
  struct dirent **dirs;

  int n = scandir("./",&dirs,fileselect,alphasort);
  if (n >= 0)
  {
    for (int cnt = 0;cnt < n;++cnt)
      puts(dirs[cnt]->d_name);
  }
  else
    perror("Cannot open directory");

	return 0;
}
