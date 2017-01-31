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

char data[1000] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0xFF, 0x03, 0x02, 0x00, 0x00 };

char httpHeader[] = "HTTP/1.1 200 OK\nContent-type: " ;  // HTTP header
char httpMimeTypeHTML[] = "text/html\n\n" ;              // HTML MIME type
char httpMimeTypeScript[] = "text/plain\n\n" ;           // TEXT MIME type

char page[100];
char method[100];

int main()
{
	char buf[100];
	int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
	{
		printf("socket ok\n");
	}
	int optval = 1;
	setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port = htons(1100)
	};

	if (bind(sock,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		perror("bind error");
		close(sock);
		return 1;
	}
	else
	{
		printf("bind ok\n");
	}

	if (listen(sock,10) == -1)
	{
		perror("listen error");
		close(sock);
		return 1;
	}
	else
	{
		printf("listen ok\n");
	}

	//while(1)
	//{
		int msgsock = accept(sock,NULL,NULL);
		if (msgsock == -1)
		{
			perror("accept error");
			close(sock);
			return 1;
		}
		else
		{
			printf("accept ok\n");
		}

		int numread = recv(msgsock,buf,100,0);
		if (numread == -1)
		{
			perror("recv error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("recv %d bytes\n",numread);
			for (int i=0; i<numread;i++)
			{
				printf("%c",buf[i]);
			}
			printf("\n");

			sscanf(buf,"%s %s HTTP/1.1/n",method, page);

			printf("method %s\n", method);

			printf("requested %s page\n",page);
		}

		if (strncmp(page,"/",1) == 0)
			strcpy(page,"/index.html");

		int webpage = open(&page[1],O_RDONLY);

		if (webpage == -1)
		{
			perror(page);
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("open webpage ok");
			numread = read(webpage,data,1000);
			if (numread == -1)
			{
				perror("read error");
				close(webpage);
				close(msgsock);
				close(sock);
				return 1;
			}
			else
			{
				printf("read %d bytes\n",numread);
				close(webpage);
			}
		}

		int numwrite = send(msgsock,httpHeader,strlen(httpHeader),0);
		if (numwrite == -1)
		{
			perror("send http header error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("send %d bytes http header ok\n",numwrite);
		}

		numwrite = send(msgsock,httpMimeTypeHTML,strlen(httpMimeTypeHTML),0);
		if (numwrite == -1)
		{
			perror("send mime type error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("send %d bytes mime type ok\n",numwrite);
		}

		numwrite = send(msgsock,data,strlen(data),0);
		if (numwrite == -1)
		{
			perror("send error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("send %d bytes webpage ok\n",numwrite);
		}

		if (shutdown(msgsock, 2) == -1)
		{
			perror("shutdown error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			printf("shutdown ok\n");
		}
		close(msgsock);
	//}
	close(sock);

	return 0;
}
