#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHUNK 10

int main()
{
  char * buf = malloc(CHUNK+1);
  int chunkcounter, totalcounter = 0, limit = CHUNK;

  FILE * mypipe = popen("cat", "r");

  while (1)
  {
    chunkcounter = fread(&buf[totalcounter], 1, CHUNK, mypipe);
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
        char * newbuf = realloc(buf,limit+1);
        if (newbuf == NULL)
        {
          puts("realloc break");
          break;
        }
        else
          buf = newbuf;
      }
      else
      {
        puts("counter break");
        break;
      }
    }
  }
  pclose(mypipe);

  buf[totalcounter] = '\0';
  printf("total length %d, allocated %d, last chunk %d\n", totalcounter, limit, chunkcounter);
  fputs(buf, stdout);
}
