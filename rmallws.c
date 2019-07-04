/*
**  Originally published as part of the MicroFirm Function Library
**
**  Copyright 1986, S.E. Margison
**  Copyright 1989, Robert B.Stout
**
**  Subset version released to the public domain, 1991
**
**  remove all whitespace from a string
*/

#include <stdio.h>
#include <ctype.h>

#define NUL '\0'

char *rmallws(char *str)
{
      char *obuf, *nbuf;

      for (obuf = str, nbuf = str; *obuf && obuf; ++obuf)
      {
            if (!isspace(*obuf))
                  *nbuf++ = *obuf;
      }
      *nbuf = NUL;
      return str;
}
