/*
**  STRREV.C - reverse a string in place
**
**  public domain by Bob Stout
*/

#include <string.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

#ifdef TEST

#include <stdio.h>

int main(int argc, char *argv[])
{
      while (--argc)
      {
            printf("\"%s\" backwards is ", *++argv);
            printf("\"%s\"\n", strrev(*argv));
      }
}

#endif /* TEST */
