#include <assert.h>
#include <stdio.h>

int main()
{
  int x = 3;
  assert(x==3);
  printf("so far so good\n");
  assert(x==4);

  return 0;
}

