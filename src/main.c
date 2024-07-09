#include "regex.h"

int main(void)
{
  i32 pos = RETest("def .+\\(.*\\)", "def foo(x, y) x + y");
  printf("%d\n", pos);
}
