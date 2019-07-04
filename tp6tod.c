/*
** Convert Turbo Pascal 6-byte reals to C double format
** Written by Thad Smith III, Boulder, CO.  12/91
** Tested on TC 2.01, BC++ 2.0/3.0, QC 2.50, Power C 2.0.1, ZTC 3.0
** Contributed to the Public Domain.
*/

#include <math.h>
#include <string.h>
#ifdef TEST
 #include <stdio.h>
#endif

/*
** Specify packed structures.
** Note: This may not work on some compilers.
*/

#if __TURBOC__ > 0x0201
 #pragma option -a-
#elif defined __ZTC__
 #pragma ZTC align 1
#else   /* MSC, WATCOM */
 #pragma pack(1)
#endif

double tp6_to_double(const unsigned char *tp6)
{
      struct {
            unsigned char be  ;     /* biased exponent           */
            unsigned int  v1  ;     /* lower 16 bits of mantissa */
            unsigned int  v2  ;     /* next  16 bits of mantissa */
            unsigned int  v3:7;     /* upper  7 bits of mantissa */
            unsigned int  s :1;     /* sign bit                  */
      } real;

      memcpy (&real, tp6, 6);
      if (real.be == 0)
            return 0.0;
      return (((((128 +real.v3) * 65536.0) + real.v2) * 65536.0 + real.v1) *
            ldexp ((real.s? -1.0: 1.0), real.be - (129+39)));
}

#ifdef TEST

/*
** This test program reads 6-byte values, one per line, in
** 12-digit hexadecimal format from stdin, converts to a double,
** then prints it.
*/

void main(void)
{
      unsigned char c[6];
      int buf[6];
      int i, n;

      for (;;)
      {
            n = scanf (" %2x%2x%2x%2x%2x%2x", &buf[0], &buf[1], &buf[2],
                                              &buf[3], &buf[4], &buf[5]);
            if (n <= 0)
                  break;
            for (i=0; i < 6; i++)
            {
                  c [i] = buf[i];
                  printf ("%2.2x", buf[i]);
            }
            printf (" =  %lg\n", tp6_to_double (c));
      }
      return 0;
}

#endif
