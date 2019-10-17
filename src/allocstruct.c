#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ctype_enum { BUILTIN, PROTO, FACE, OPTION, SETTING, COMMAND, CUESETTING };

struct complement
{
  char * command;
  enum ctype_enum ctype;
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

typedef cmpstr_t *callback_func_t (char *);

char *builtincommands[] = {"show","acquire","validate",NULL};

char * builtinvalues(const char * text, int len)
{
  static int valueindex = 0;

  while (builtincommands[valueindex] != NULL)
  {
    if (strncmp(builtincommands[valueindex], text, len)==0)
    {
      return strdup(builtincommands[valueindex++]);
    }
    else
    {
      valueindex++;
    }
  }
  valueindex = 0;
  return NULL;
}

cmpstr_t test1 = { .command = "hello" };

cmpstr_t *callback(char * inputstring)
{
  cmpstr_t * element;
  element = (cmpstr_t *)malloc(sizeof(cmpstr_t));

  element->command = "hello";

  static int i = 0;
  i++;
  if (i < 10)
    return element;
  else
    return NULL;
}

void array_allocate(char * inputstring, callback_func_t *cb_func, cmplist_t * list)
{
  //cmplist_t list = { .complecount = 0};
  cmpstr_t *element;
  //string_list = (char **)malloc(sizeof (char *));

  while (element = (*cb_func)(inputstring))
  {
    list->complecount++;
    list->complelist = (cmpstr_t **)realloc(list->complelist, sizeof(cmpstr_t *) * list->complecount);
    list->complelist[list->complecount-1] = element;
  }

  for (int i = 0; i < list->complecount; i++)
  {
    puts(list->complelist[i]->command);
  }
  printf("%d\n",list->complecount);

//    return counter;
//  return list;
}

int main()
{
  cmplist_t list = { .complecount = 0};
  array_allocate("hello", callback, &list);
//  cmpstr_t **list = array_allocate(callback);
  printf("%d\n",list.complecount);
  for (int i = 0; i < list.complecount; i++)
    puts(list.complelist[i]->command);
	return 0;
}
