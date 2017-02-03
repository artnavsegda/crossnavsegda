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

char data[1000];
char buf[1000];

char httpHeader[1000] = "HTTP/1.1 200 OK"; // HTTP header
char * httpMimeType;
char httpMimeTypeHTML[] = "\nContent-type: text/html\n\n" ;              // HTML MIME type
char httpMimeTypeScript[] = "\nContent-type: application/javascript\n\n" ;           // JS MIME type
char httpMimeTypeText[] = "\nContent-type: text/plain\n\n" ;           // TEXT MIME type
char httpMimeTypeCSS[] = "\nContent-type: text/CSS\n\n" ;           // CSS MIME type

//char page[100];
//char method[100];
char *page;
char *method;

char str[100] = "one=1\n\
two=2\n\
three=3.14\n\
ip=192.168.1.150";

char *options[100];
char *values[100];
int optisize;

char * getmyopt(char *parameter)
{
	for (int i=0;i<optisize;i++)
		if (strcmp(options[i],parameter)==0)
			return values[i];
	return NULL;
}

void setopt(char *parameter, char *newset)
{
	int found = 0;
	for (int i=0;i<optisize;i++)
	{
		if (strcmp(options[i],parameter)==0)
		{
			if (strlen(newset)>strlen(values[i]))
			{
				found = 1;
				//values[i] = newset; //just change the pointer
				values[i] = malloc(strlen(newset)); //or to allocate new memory ?
				strcpy(values[i],newset);
			}
			else
				strcpy(values[i],newset);
		}
	}
	if (found == 0)
	{
		options[optisize] = parameter;
		values[optisize] = newset;
		optisize++;
	}
}

void makeopt(void)
{
	FILE * setfile = fopen("./settings.txt","r");
	if (setfile != NULL)
	{
		int numread = fread(str,1,100,setfile);
		printf("read %d bytes\n",numread);
		str[numread] = '\0';
	}
	int i = 0;
	options[i] = strtok(str," \n");
	while (options[i]!=NULL)
		options[++i] = strtok(NULL," \n");
	optisize = i;
	for (i=0;i<optisize;i++)
	{
		strtok(options[i],"=");
		values[i] = strtok(NULL,"=");
	}
}

int main()
{
	makeopt();
	int hv;
	char *buf2;
	int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock == -1)
	{
		perror("socket error");
		return 1;
	}
	else
		printf("socket ok\n");
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
		printf("bind ok\n");

	if (listen(sock,10) == -1)
	{
		perror("listen error");
		close(sock);
		return 1;
	}
	else
		printf("listen ok\n");

	while(1)
	{
		int msgsock = accept(sock,NULL,NULL);
		if (msgsock == -1)
		{
			perror("accept error");
			close(sock);
			return 1;
		}
		else
			printf("accept ok\n");

		int numread = recv(msgsock,buf,1000,0);
		if (numread == -1)
		{
			perror("recv error");
			close(msgsock);
			close(sock);
			return 1;
		}
		else
		{
			buf[numread] = 0;
			printf("recv %d bytes\n",numread);
			//for (int i=0; i<numread;i++)
			//{
			//	printf("%c",buf[i]);
			//}
			printf("\n");
			method = strtok(buf," ");
			page = strtok(NULL," ");
			//sscanf(buf,"%s %s HTTP/1.%d\n",method, page, &hv);
			printf("method %s\n", method);
			printf("requested %s page\n",page);
			buf2 = strtok(NULL,"");
			puts(buf2);
		}

		if (strlen(page) == 1)
			strcpy(page,"/index.html");

		if (strcmp(page,"/special")==0)
		{
			printf("requested special page\n");
			puts(strstr(buf2,"\r\n\r\n")+4);
			printf("thats what she said\n");
			sprintf(httpHeader,"HTTP/1.1 %d OK",200);
			httpMimeType = httpMimeTypeText;
			strcpy(data,getmyopt(strstr(buf2,"\r\n\r\n")+4));
			//sprintf(data,"you're so special");
		}
		else
		{
			int webpage = open(&page[1],O_RDONLY);
			if (webpage == -1)
			{
				perror(page);
				sprintf(httpHeader,"HTTP/1.1 %d Not Found",404);
				httpMimeType = httpMimeTypeHTML;
				sprintf(data,"<!doctype html><html><head><title>404 Not Found</title></head><body><p>%s not found</p></body></html>",page);
				//close(msgsock);
				//close(sock);
				//return 1;
			}
			else
			{
				printf("open webpage %s ok\n",page);
				numread = read(webpage,data,1000);
				data[numread] = 0;
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
					sprintf(httpHeader,"HTTP/1.1 %d OK",200);
					close(webpage);
					if (strcmp(strchr(page,'.'),".html")==0)
						httpMimeType = httpMimeTypeHTML;
					else if (strcmp(strchr(page,'.'),".js")==0)
						httpMimeType = httpMimeTypeScript;
					else if (strcmp(strchr(page,'.'),".txt")==0)
						httpMimeType = httpMimeTypeText;
					else if (strcmp(strchr(page,'.'),".css")==0)
						httpMimeType = httpMimeTypeCSS;
				}
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

		numwrite = send(msgsock,httpMimeType,strlen(httpMimeType),0);
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
	}
	close(sock);

	return 0;
}
