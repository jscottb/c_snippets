#include <stdio.h>

int another_function(int x) { return! ((~(~0U>>1)|x)&x -1) ;}

int main(void)
{
      int i;

      for (i = 0; i < 256; ++i)
            printf("%3d: %d\n", i, another_function(i));
      return 0;
}
