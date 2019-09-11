#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();
  int status;

  if (pid == 0)
  {
    puts("child process");
    char * argv_list[] = {"ls","-lart","/home",NULL};
    execv("/bin/ls",argv_list);
    puts("ls before");
    exit(0);
  }
  else
  {
    printf("parent process child pid is %d\n",pid);

    waitpid(pid, &status,0);

    exit(0);

  }

  return 0;
}

