#include <ftw.h>
#include <stdio.h>

int list(const char *name, const struct stat *status, int type)
{
//  switch (type)
//  {
//    case FTW_F:
//      puts
//  }
  puts(name);
  return 0;
}

int main()
{
  ftw("./", list, 1);
}

