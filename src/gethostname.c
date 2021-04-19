#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main()
{
  char hostname[255];
  gethostname(hostname, 255);
  puts(hostname);
}

