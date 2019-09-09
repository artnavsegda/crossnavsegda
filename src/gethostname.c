#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main()
{
  char hostname[HOST_NAME_MAX];
  gethostname(hostname, HOST_NAME_MAX);
  puts(hostname);
}

