int bitcount(long i)
{
      i = ((i & 0xAAAAAAAA) >>  1) + (i & 0x55555555);
      i = ((i & 0xCCCCCCCC) >>  2) + (i & 0x33333333);
      i = ((i & 0xF0F0F0F0) >>  4) + (i & 0x0F0F0F0F);
      i = ((i & 0xFF00FF00) >>  8) + (i & 0x00FF00FF);
      i = ((i & 0xFFFF0000) >> 16) + (i & 0x0000FFFF);
      return (int)i;
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

#define plural_text(n) &"s"[(1 == (n))]

void main(int argc, char *argv[])
{
      long n;

      while(--argc)
      {
            int i;

            n = atol(*++argv);
            i = bitcount(n);
            printf("%ld contains %d bit%s set\n",
                  n, i, plural_text(i));
      }
}

#endif /* TEST */
