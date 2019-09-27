#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main(int argc, char *argv[], char *envp[])
{
  int i = 0;
  while(envp[i] != NULL)
  {
    puts(envp[i]);
    i++;
  }
  puts(getenv("USER"));
	return 0;
}
