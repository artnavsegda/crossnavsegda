#include <stdio.h>

typedef char *callback_func_t (void);

char * callback(void)
{
  static int i = 0;
  i++;
  if (i < 10)
    return "hoba";
  else
    return NULL;
}

char ** array_allocate(callback_func_t *cb_func)
{
  char *string;
  while (string = (*cb_func)())
  {
    puts(string);
  }
}

int main()
{
	array_allocate(callback);
	return 0;
}
