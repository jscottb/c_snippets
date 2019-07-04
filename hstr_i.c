/*
**  Originally published as part of the MicroFirm Function Library
**
**  Copyright 1986, S.E. Margison
**  Copyright 1989, Robert B.Stout
**
**  Subset version released to the public domain, 1992
**
**  Make an ascii hexadecimal string into an integer.
*/

#include <stdio.h>
#include <ctype.h>

unsigned int hstr_i(char *cptr)
{
      unsigned int i, j = 0;

      while (cptr && *cptr && isxdigit(*cptr))
      {
            i = *cptr++ - '0';
            if (9 < i)
                  i -= 7;
            j <<= 4;
            j |= (i & 0x0f);
      }
      return(j);
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
      char *arg;
      unsigned int x;

      while (--argc)
      {
            x = hstr_i(arg = *++argv);
            printf("Hex %s = %d\n", arg, x, x);
      }
      return EXIT_SUCCESS;
}

#endif /* TEST */
