#include <stdio.h>

FILE * my_popen_read (char * command, char *argv[], char *envp[])
{
    int fd[2];
    int read_fd, write_fd;
    int pid;
    pipe(fd);
    read_fd = fd[0];
    write_fd = fd[1];
    pid = fork();
    if (pid == 0) {
        close(read_fd);
        dup2(write_fd,1);
        close(write_fd);
        execve(command,argv,envp);
        return NULL;
    } else {
        close(write_fd);
        return fdopen(read_fd, "r");
    }
}

FILE * my_popen_write (char * command, char *argv[], char *envp[])
{
    int fd[2];
    int read_fd, write_fd;
    int pid;
    pipe(fd);
    read_fd = fd[0];
    write_fd = fd[1];
    pid = fork();
    if (pid == 0) {
        close(write_fd);
        dup2(read_fd,0);
        close(read_fd);
        execve(command,argv,envp);
        return NULL;
    } else {
        close(read_fd);
        return fdopen(write_fd, "w");
    }
}

int main()
{
  FILE *fp;
  fp = popen("ls", "w");

  if (fp == NULL)
    puts("handle error");

  pclose(fp);
}
