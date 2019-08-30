#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *argarray[100];
  int i;
  for (i = 0; i < argc; i++)
  {
    argarray[i]=argv[i];
  }
  argarray[i] = "Something";
  argarray[i+1] = NULL;

  execve("./printargs",argarray,NULL);

  return 1;
}

