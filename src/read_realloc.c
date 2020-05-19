#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHUNK 10

int main()
{
  char * buf = malloc(CHUNK+1);
  int chunkcounter, totalcounter = 0, limit = CHUNK;

  while (1)
  {
    chunkcounter = read(STDIN_FILENO, &buf[totalcounter], CHUNK);
    if (chunkcounter == -1) 
    {
      perror("read error");
      exit(0);
    }
    else 
    {
      totalcounter += chunkcounter;
      if (chunkcounter == CHUNK)
      {
        limit += CHUNK;
        if (realloc(buf,limit+1) == NULL)
        {
          puts("realloc break");
          break;
        }
      }
      else
      {
        puts("counter break");
        break;
      }
    }
  }

  buf[totalcounter] = '\0';
  printf("total length %d, allocated %d, last chunk %d\n", totalcounter, limit, chunkcounter);
  fputs(buf, stdout);
}

