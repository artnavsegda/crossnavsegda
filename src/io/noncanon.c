#include <unistd.h>
#include <stdio.h>
#include <termios.h>

int main(void)
{
	struct termios canon, noncanon = { .c_lflag = 0 };
	tcgetattr(STDIN_FILENO, &canon);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &noncanon);
	sleep(10);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &canon);
}
