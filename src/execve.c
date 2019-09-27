#include <stdio.h>
#include <unistd.h>

int main()
{
  char *myenv[] = {
    "hello=me",
    NULL
  };
  execve("./environ",NULL,myenv);
	return 0;
}
