#include <stdio.h>
#include <unistd.h>

int main()
{
  char *myenv[] = {
    "hello=me",
    NULL
  };

  char *myargv[] = {
    "env",
    NULL
  };

  execve("/usr/bin/env",myargv,myenv);
	return 0;
}
