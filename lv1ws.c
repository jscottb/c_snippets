/*
**  Originally published as part of the MicroFirm Function Library
**
**  Copyright 1987-88, Robert B.Stout
**
**  Subset version released to the public domain, 1992
**
**  Makes all whitespace single spaces. Passed a string, lv1ws()
**  converts all multiple whitespace characters to single spaces.
*/

#include <ctype.h>

void lv1ws(char *str)
{
      char *ibuf = str, *obuf = str;
      int i = 0, cnt = 0;

      while(*ibuf)
      {
            if(isspace(*ibuf) && cnt)
                  ibuf++;
            else
            {
                  if (!isspace(*ibuf))
                        cnt = 0;
                  else
                  {
                        *ibuf = ' ';
                        cnt = 1;
                  }
                  obuf[i++] = *ibuf++;
            }
      }
      obuf[i] = '\0';
}
