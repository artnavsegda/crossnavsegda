#include <ftw.h>

int main()
{
  ftw("./", list, 1);
}

