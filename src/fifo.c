#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    char str[80];
    while (1)
    {
        fd = open(myfifo,O_RDONLY);
        read(fd, str, 80);
        printf("%s\n", str);
    }
    close(fd);
    return 0;
}
