#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

void drop(int dropstatus, char *dropdesc)
{
        if (dropstatus == -1)
        {
                perror(dropdesc);
                exit(1);
        }
}

void drop2(char *dropstatus, char *dropdesc)
{
        if (dropstatus == NULL)
        {
                perror(dropdesc);
                exit(1);
        }
}

int main(void)
{
        char buf[10000];
        int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        drop(sock,"socket error");
        int reuseaddr = 1;
        setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
        struct sockaddr_in server = {
                .sin_family = AF_INET,
                .sin_addr.s_addr = INADDR_ANY,
                .sin_port = htons(1100)
        };
        drop(bind(sock,(struct sockaddr *)&server,sizeof(server)),"bind error");
        drop(listen(sock,10),"listen error");
        while(1)
        {
                int msgsock = accept(sock,NULL,NULL);
                drop(msgsock,"accept error");
                int numread = recv(msgsock,buf,10000,0);
                drop(numread,"recv error");
                buf[numread] = '\0';
                char *method = strtok(buf," ");
                char *page = strtok(NULL," ");
                char *buf2 = strtok(NULL,"");
                if (strlen(page) == 1)
                        page = "/index.html";
                int webpage = open(&page[1],O_RDONLY);
                drop(webpage,"404 placeholder");
                char *data = malloc(filesize(webpage)+1);
                drop2(data,"out of memory");
                numread = read(webpage,data,filesize(webpage)+1);
                drop(numread,"read error");
                data[numread] = '\0';
                close(webpage);
                char *httpMimeType = getmime(page);
                drop(send(msgsock,"HTTP/1.1 200 OK",15,0),"send http header error");
                drop(send(msgsock,httpMimeType,strlen(httpMimeType),0),"send mime type error");
                drop(send(msgsock,data,strlen(data),0),"send webpage error");
                free(data);
                drop(shutdown(msgsock,2),"shutdown error");
                close(msgsock);
        }
        close(sock);
        return 0;
}
