#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  while ((int opt = getopt(argc, argv, "nt")) != -1)
  {
    switch (opt)
    {
      case 'n':
        break;
      case 't':
        break;
    }
  }
}
