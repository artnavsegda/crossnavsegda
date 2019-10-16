#include <stdio.h>

typedef void callback_func_t (void);

void callback(void)
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
