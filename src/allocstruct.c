#include <stdio.h>
#include <stdlib.h>

enum domains { PROTO, FACE, OPTION, SETTING, COMMAND };

struct complement
{
  char * command;
  enum domains domain;
  char * description;
};

typedef struct complement cmpstr_t;

struct complestruct
{
  char * locode;
  int complecount;
  cmpstr_t complelist[];
};

typedef cmpstr_t *callback_func_t (void);

cmpstr_t test1;

cmpstr_t *callback(void)
{
  static int i = 0;
  i++;
  if (i < 10)
    return &test1;
  else
    return NULL;
}

/*char ** array_allocate(callback_func_t *cb_func)
{
  char *string;
  char **string_list = NULL;
  //string_list = (char **)malloc(sizeof (char *));
  int counter = 0;

  while (string = (*cb_func)())
  {
    counter++;
    string_list = (char **)realloc(string_list, sizeof(char *) * counter);
    string_list[counter-1] = string;
  }
  printf("%d\n",counter);

  for (int i = 0; i < counter; i++)
  {
    puts(string_list[i]);
  }

  return string_list;
}*/

int main()
{
  //array_allocate(callback);
	return 0;
}
