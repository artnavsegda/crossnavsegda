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

//struct complestruct
//{
//  char * locode;
//  int complecount;
//  cmpstr_t **complelist;
//};

typedef cmpstr_t *callback_func_t (void);

cmpstr_t test1 = { .command = "hello" };

cmpstr_t *callback(void)
{
  static int i = 0;
  i++;
  if (i < 10)
    return &test1;
  else
    return NULL;
}

int array_allocate(callback_func_t *cb_func, cmpstr_t **list)
{
  cmpstr_t *element;
  //cmpstr_t **list = NULL;
  //string_list = (char **)malloc(sizeof (char *));
  int counter = 0;

  while (element = (*cb_func)())
  {
    counter++;
    list = (cmpstr_t **)realloc(list, sizeof(cmpstr_t *) * counter);
    list[counter-1] = element;
  }
  printf("%d\n",counter);

  for (int i = 0; i < counter; i++)
  {
    puts(list[i]->command);
  }

  return counter;
//  return string_list;
}

int main()
{
  cmpstr_t **list = NULL;
  array_allocate(callback, list);
	return 0;
}
