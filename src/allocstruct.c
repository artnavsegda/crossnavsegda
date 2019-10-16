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
  cmpstr_t **complelist;
};

typedef struct complestruct cmplist_t;

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

void array_allocate(callback_func_t *cb_func)
{
  cmplist_t list = { .complecount = 0};
  cmpstr_t *element;
  //string_list = (char **)malloc(sizeof (char *));

  while (element = (*cb_func)())
  {
    list.complecount++;
    list.complelist = (cmpstr_t **)realloc(list.complelist, sizeof(cmpstr_t *) * list.complecount);
    list.complelist[list.complecount-1] = element;
  }

  for (int i = 0; i < list.complecount; i++)
  {
    puts(list.complelist[i]->command);
  }
  printf("%d\n",list.complecount);

//    return counter;
//  return list;
}

int main()
{
  array_allocate(callback);
//  cmpstr_t **list = array_allocate(callback);
//  printf("%d\n",counter);
//  for (int i = 0; i < 9; i++)
//    puts(list[i]->command);
	return 0;
}
