#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char temp[1000];

  char *argarray[100];
  int i;
  for (i = 0; i < argc; i++)
  {
    argarray[i]=argv[i];
  }

  temp[read(STDIN_FILENO,temp,1000)] = '\0';

  argarray[i] = temp;
  argarray[i+1] = NULL;

  execve("./printargs",argarray,NULL);

  return 1;
}

