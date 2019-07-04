/*
**  DBLROUND.C - Rounds a double to the nearest whole number
**  public domain by Ross Cottrell
*/

#include <float.h>
#include <limits.h>
#include <assert.h>

double round(double x)
{
      assert(1 == FLT_ROUNDS);
      x += 1.0 / DBL_EPSILON;
      return x - 1.0 / DBL_EPSILON;
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
      double val;
      char *dummy;

      while (--argc)
      {
            val = strtod((const char *)(*(++argv)), &dummy);
            printf("round(%g) = ", val);
            printf("%.12g\n", round(val));
      }
}

#endif /* TEST */
