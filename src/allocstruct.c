#include <stdio.h>

enum domains { PROTO, FACE, OPTION, SETTING, COMMAND };

struct complement
{
  char * command;
  enum domains domain;
  char * description;
};

struct complestruct
{
  char * locode;
  int complecount;
  struct complement complelist[];
};



int main()
{
  printf("fuck");
	return 0;
}
