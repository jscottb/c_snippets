/*
**  Originally published as part of the MicroFirm Function Library
**
**  Copyright 1986, S.E. Margison
**  Copyright 1989, Robert B.Stout
**
**  Subset version released to the public domain, 1991
**
**  remove leading whitespace from a string
*/

#include <ctype.h>
#include <string.h>

#define NUL '\0'

char *rmlead(char *str)
{
      char *obuf;

      for (obuf = str; obuf && *obuf && isspace(*obuf); ++obuf)
            ;
      if (str != obuf)
            strcpy(str, obuf);
      return str;
}
