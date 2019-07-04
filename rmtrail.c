/*
**  Originally published as part of the MicroFirm Function Library
**
**  Copyright 1986, S.E. Margison
**  Copyright 1989, Robert B.Stout
**
**  Subset version released to the public domain, 1991
**
**  remove trailing whitespace from a string
*/

#include <string.h>
#include <ctype.h>

#define NUL '\0'

char *rmtrail(char *str)
{
      int i;

      if (0 != (i = strlen(str)))
      {
            while (--i >= 0)
            {
                  if (!isspace(str[i]))
                        break;
            }
            str[++i] = NUL;
      }
      return str;
}
