#include <ftw.h>
#include <stdio.h>
#include <string.h>

int list(const char *name, const struct stat *status, int type)
{
//  switch (type)
//  {
//    case FTW_F:
//      puts
//  }
  char *ptr = rindex(name, '.');
  if ((ptr!=NULL) && ((strcmp(ptr,".c")==0)))
    puts(name);
  return 0;
}

int main()
{
  ftw("./", list, 1);
}

