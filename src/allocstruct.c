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

char *builtincommands[] = {"one","onetwo","onethre",NULL};

char * builtinvalues(const char * text, int len)
{
  static int valueindex = 0;

  while (builtincommands[valueindex] != NULL)
  {
    if (strncmp(builtincommands[valueindex], text, len)==0)
    {
      return builtincommands[valueindex++];
    }
    else
    {
      valueindex++;
    }
  }
  valueindex = 0;
  return NULL;
}

int compute_lcd_of_matches (cmplist_t * list)
{
  char **match_list; int matches; const char *text;//remove
  register int i, c1, c2, si;
  int low;		/* Count of max-matched characters. */
  int lx;

  /* If only one match, just use that.  Otherwise, compare each
     member of the list with the next, finding out where they
     stop matching. */
  if (list->complecount == 1)
    {
      list->locode = list->complelist[0]->command;
      return 1;
    }

  for (i = 1, low = 100000; i < matches; i++)
    {
	  for (si = 0;
	       (c1 = match_list[i][si]) &&
	       (c2 = match_list[i + 1][si]);
	       si++)
	    if (c1 != c2)
	      break;

      if (low > si)
	low = si;
    }

  /* If there were multiple matches, but none matched up to even the
     first character, and the user typed something, use that as the
     value of matches[0]. */
  if (low == 0 && text && *text)
    {
      match_list[0] = (char *)malloc (strlen (text) + 1);
      strcpy (match_list[0], text);
    }
  else
    {
      match_list[0] = (char *)malloc (low + 1);
      strncpy (match_list[0], match_list[1], low);
      match_list[0][low] = '\0';
    }

  return matches;
}

cmpstr_t test1 = { .command = "hello" };

cmpstr_t *callback(char * inputstring)
{
  cmpstr_t * element;
  element = (cmpstr_t *)malloc(sizeof(cmpstr_t));
  element->command = builtinvalues(inputstring, strlen(inputstring));

  if (element->command)
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
  
  if (list->complecount)
  {
    compute_lcd_of_matches(list);
  }

//  for (int i = 0; i < list->complecount; i++)
//  {
//    puts(list->complelist[i]->command);
//  }
//  printf("%d\n",list->complecount);

//    return counter;
//  return list;
}

int main()
{
  cmplist_t list = { .complecount = 0};
  array_allocate("onet", callback, &list);
//  cmpstr_t **list = array_allocate(callback);
  printf("%d\n",list.complecount);
  for (int i = 0; i < list.complecount; i++)
    puts(list.complelist[i]->command);
	return 0;
}
