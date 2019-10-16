#include <stdio.h>

typedef void callback_func_t (void);

void callback(void)
{
  puts("hoba");
}

void recv_callback(callback_func_t *cb_func)
{
  (*cb_func)();
}

int main()
{
  recv_callback(callback);
	return 0;
}
