#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char temp[1000];

  char *argarray[100];
  int i;
  for (i = 0; i < argc; i++)
  {
    argarray[i]=argv[i+1];
  }

  temp[read(STDIN_FILENO,temp,1000)] = '\0';

  argarray[i-1] = temp;
  argarray[i] = NULL;

  execve(argv[1],argarray,NULL);

  return 1;
}

