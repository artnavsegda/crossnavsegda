#include <stdio.h>
#include <stdlib.h>

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

  char **string_list;

  string_list = (char **)malloc(sizeof (char *));

  while (string = (*cb_func)())
  {
//    string_list = 


    puts(string);
  }
}

int main()
{
	array_allocate(callback);
	return 0;
}
