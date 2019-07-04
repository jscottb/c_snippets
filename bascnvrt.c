/*
**  BASCNVRT.C - Convert between number bases
**
**  public domain demo by Bob Stout
*/

#include <stdlib.h>
#ifdef TEST
 #include <stdio.h>
#endif

/*
**  Calling parameters: 1 - Number string to be converted
**                      2 - Buffer for the  converted output
**                      3 - Radix (base) of the input
**                      4 - Radix of the output
**
**  Returns: Pointer to converted output
*/

char *base_convert(const char *in, char *out, int rin, int rout)
{
      long n;
      char *dummy;

      n = strtol(in, &dummy, rin);
      return ltoa(n, out, rout);
}

#ifdef TEST

int main(int argc, char *argv[])
{
      int rin, rout;
      char buf[40];

      if (4 > argc)
      {
            puts("Usage: BASCNVRT <number> <base_in> <base_out>");
            return(-1);
      }
      rin  = atoi(argv[2]);
      rout = atoi(argv[3]);
      printf("%s (base %d) = %s (base %d)\n", argv[1], rin,
            base_convert((const char *)argv[1], buf, rin, rout), rout);
      return 0;
}

#endif
