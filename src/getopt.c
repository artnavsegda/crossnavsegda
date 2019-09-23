#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int opt;
  char * config = NULL;
  char * type = NULL;
  while ((opt = getopt(argc, argv, "nt")) != -1)
  {
    switch (opt)
    {
      case 'c': // config
        break;
      case 't': // type
        break;
    }
  }
}
