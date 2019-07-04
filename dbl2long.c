/*
**  DBL2LONG.C - Functions to round doubles to longs
**  Public domain by Ross G. Cottrell, June 1992
*/

#include <float.h>
#include <limits.h>
#include <assert.h>

/* Assume IEEE doubles, little-endian CPU, 32-bit 2's complement longs. */
/* (Actually, the assumptions made here aren't quite that gross.)       */

unsigned long dbl2ulong(double t)
{
      assert(1 == FLT_ROUNDS);
      t += 1.0 / DBL_EPSILON;
      return *(unsigned long *)&t;
}

long dbl2long(double t)
{
      assert(1 == FLT_ROUNDS);
      t += 1.0 / DBL_EPSILON + 2.0 * (LONG_MAX + 1.0);
      return *(long *)&t;
}

#ifdef TEST

#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
      while (*++argv)
      {
            printf("'%s', as a long: %ld, as an unsigned long: %lu\n",
                  *argv, dbl2long(atof(*argv)), dbl2ulong(atof(*argv)));
      }
      return 0;
}

#endif /* TEST */

/*

EXPLANATION:

The offset of 1.0/DBL_EPSILON forces the least significant bit of the
mantissa to represent the integer 1.  This may not work on all formats of
doubles, but I think it's a safe bet for IEEE compliant doubles, and any
other floating point format with a radix of 2.  When this offset is added,
the number should be rounded to the nearest representable value.  The
assertion that FLT_ROUNDS has the value of 1 is an attempt to guarantee
this.  You might check your float.h; if this isn't #defined as a constant 1
you should investigate how to ensure that it will always round to the
nearest.  If it is #defined as 1 you can safely rip out the assertions.  The
addition of 2.0*(LONG_MAX+1.0) for the signed long is to prevent the the MSB
of the mantissa being borrowed for negative inputs - if this happened, the
exponent would change and the LSB of the mantissa would no longer be worth
1.  This offset would be perfectly okay to use with the unsigned longs too
but it's unnecessary for them, unless you want to get the answer correct
modulo 2^^32 for negatives.

*/
