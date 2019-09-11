#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork();

  if (pid == 0)
  {
    puts("child process");
  }
  else
  {
    printf("parent process child pid is %d\n",pid);
  }

  return 0;
}

