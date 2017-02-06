#include <stdio.h>

#define MAXOPT 1000

struct settings {
        char *options[MAXOPT];
        char *values[MAXOPT];
        int optisize = 0;
}

void setopt(struct settings *myset, char *parameter, char *newset)
{
	int found = 0;
	for (i=0;i<myset->optisize;i++)
	{
		if (strcmp(myset->options[i],parameter)==0)
		{
			if (strlen(newset)>strlen(myset->values[i]))
			{
				found = 1;
				//values[i] = newset; //just change the pointer
				myset->values[i] = malloc(strlen(newset)); //or to allocate new memory ?
				strcpy(myset->values[i],newset);
			}
			else
				strcpy(myset->values[i],newset);
		}
	}
	if (found == 0)
	{
		myset->options[myset->optisize] = malloc(strlen(parameter));
                strcpy(parameter,myset->options[myset->optisize]);
		myset->values[myset->optisize] = malloc(strlen(newset));
                strcpy(newset,myset->values[myset->optisize]);
		myset->optisize++;
	}
}

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

long long filesize(int fd)
{
	struct stat filestat;
	drop(fstat(fd,&filestat),"file status error");
	return filestat.st_size;
}

void feedopt(char *filename)
{
        char *options[MAXOPT];
        char *values[MAXOPT];
        FILE * setfile = fopen(filename,"r");
        drop2(setfile);
        char *data = malloc(filesize(setfile)+1);
        int numread = fread(data,1,filesize(setfile),setfile);
        drop(numread);
        str[numread] = '\0';
        fclose(setfile);
        int i = 0;
        options[i] = strtok(str," \n");
        while (options[i]!=NULL)
                options[++i] = strtok(NULL," \n");
        int optisize = i;
        for (i=0;i<optisize;i++)
        {
                strtok(options[i],"=");
                values[i] = strtok(NULL,"=");
        }
        for (i=0;i<optisize;i++)
                setopt(NULL,options[i],values[i]);
        free(data);
}

int main(void)
{

}
