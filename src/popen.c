#include <stdio.h>

int main()
{
  FILE *fp;
  fp = popen("ls", "w");

  if (fp == NULL)
    puts("handle error");

  pclose(fp);
}

