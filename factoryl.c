/*
**  FACTORYL.C
**
**  Original Copyright 1992 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/

#include <math.h>
#include <float.h>
#include <assert.h>

#define dfrac(x) ((x)-dround(x))

/* Use #defines for Permutations and Combinations     */

#define log10P(n,r) (log10factorial(n)-log10factorial((n)-(r)))
#define log10C(n,r) (log10P((n),(r))-log10factorial(r))

#ifndef PI
 #define PI 3.14159265358979323846
#endif

#define SQRT2PI sqrt(2 * PI)
#define ONESIXTH (1.0/6.0)

/*
**  DROUND.C - Rounds a double to the nearest whole number
**  public domain by Ross Cottrell
*/

double dround(double x)
{
      assert(1 == FLT_ROUNDS);
      x += 1.0 / DBL_EPSILON;
      return x - 1.0 / DBL_EPSILON;
}

/*
**  log10factorial()
**
**  Returns the logarithm (base 10) of the factorial of a given number.
**  The logarithm is returned since this allows working wil extremely
**  large values which would otherwise overflow the F.P. range.
**
**  Parameters: 1 - Number whose factorial to return.
**
**  Returns: log10() of the passed value, -1.0 if error
**
*/

double log10factorial(double N)
{
      if (N < 40)                         /* Small, explicitly compute  */
      {
            int i;
            double f;

            for (i = 1, f = 1.0; i <= (int)N; ++i)
                  f *= i;
            return log10(f);
      }
      else                                /* Large, use approximation   */
      {
            return log10(SQRT2PI)+((N + 0.5) *
                  (log10(sqrt(N * N + N + ONESIXTH) / exp(1))));
      }
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
      double f, lf;
      char *dummy;

      while (--argc)
      {
            f  = strtod((const char *)(*(++argv)), &dummy);
            lf = log10factorial(f);
            if (171.0 > f)
                  printf("%.14g! = %.14g\n", f, pow(10.0, lf));
            else
            {
                  printf("%.14g! = %.14ge+%ld\n", f,
                        pow(10.0, dfrac(lf)), (long)dround(lf));
            }
      }
      lf = log10C(1000000,750000);
      printf("\nJust to dazzle with you with big numbers:\n"
            "C(1000000,750000) = %.14ge+%ld\n",
            pow(10.0, dfrac(lf)), (long)dround(lf));
      lf = log10P(1000000,750000);
      printf("\n...once more:\n"
            "P(1000000,750000) = %.14ge+%ld\n",
            pow(10.0, dfrac(lf)), (long)dround(lf));
}

#endif /* TEST */
