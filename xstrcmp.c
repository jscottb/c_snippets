/*
**  xstrcmp() - compares strings using DOS wildcards
**              'mask' may contain '*' and '?'
**               returns 1 if 's' matches 'mask', otherwise 0
**               public domain by Steffen Offermann 1991
*/


int xstrcmp (char *mask, char *s)
{
      while (*mask)
      {
            switch (*mask)
            {
            case '?':
                  if (!*s)
                        return (0);
                  s++;
                  mask++;
                  break;

            case '*':
                  while (*mask == '*')
                        mask++;
                  if (!*mask)
                        return ( 1 );
                  if (*mask == '?')
                        break;
                  while (*s != *mask)
                  {
                        if (!*s)
                              return (0);
                        s++;
                  }
                  s++;
                  mask++;
                  break;

            default:
                  if (*s != *mask)
                        return (0);
                  s++;
                  mask++;
            }
      }

      if (!*s && *mask)
            return (0);
      return ( 1 );
}

#ifdef TEST

#include <stdio.h>

void main(int argc, char *argv[])
{
      if (3 != argc)
      {
            puts("Usage: XSTRCMP string_1 string_2");
            return;
      }
      printf("xstrcmp(\"%s\", \"%s\") returned %d\n", argv[1], argv[2],
            xstrcmp(argv[1], argv[2]));
}

#endif /* TEST */
