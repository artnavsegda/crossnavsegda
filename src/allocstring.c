#include <stdio.h>

typedef char *callback_func_t (void);

char * callback(void)
{
  puts("hoba");
}

char ** array_allocate(callback_func_t *cb_func)
{
	(*cb_func)();
}

int main()
{
	array_allocate(callback);
	return 0;
}
