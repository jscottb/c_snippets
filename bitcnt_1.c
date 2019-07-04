/*
**  Bit counter by Ratko Tomic
*/

int bit_count(long x)
{
        int n = 0;
/*
** The loop will execute once for each bit of x set, this is in average
** twice as fast as the shift/test method.
*/
        if (x) do
              n++;
        while (0 != (x = x&(x-1)))
              ;
        return(n);
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
            i = bit_count(n);
            printf("%ld contains %d bit%s set\n",
                  n, i, plural_text(i));
      }
}

#endif /* TEST */
