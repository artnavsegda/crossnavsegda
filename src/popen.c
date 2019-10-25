#include <stdio.h>
#include <unistd.h>

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

char *myargv[] = { "/bin/cat", NULL };

int main(int argc, char *argv[])
{
  FILE *fp;
  //fp = my_popen_read("/bin/ls", argv, NULL);
  fp = my_popen_write("/bin/cat", myargv, NULL);
  if (fp == NULL)
    puts("handle error");
  puts("pipe open");
  sleep(1);
  fwrite("hello\n\0", 1, 7, fp);
  puts("data sent");
  sleep(1);
  fflush(fp);
  puts("data flushed");
  sleep(1);
  fclose(fp);
  puts("pipe closed");
  sleep(1);
}
