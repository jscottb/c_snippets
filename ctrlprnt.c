/*
**  Print a line of text, displaying Ctrl characters using leading carets
**  public domain by Bob Stout
*/

void ctrl_print(char *line)
{
      while (*line)
      {
            if (' ' > *line)
            {
                  putchar('^');
                  putchar('@' + (*line++));
            }
            else  putchar(*line++);
      }
      if (!strcmp((line - 2), "\x0d\x0a") || !strcmp((line - 2), "\x0a\x0d"))
            putchar('\n');
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main(void)
{
      char *p, *test = "This is a test";

      for (p = strupr(test); *p; ++p)
      {
            if (isalpha(*p))
                  *p = *p - 64;
      }
      ctrl_print(test);
}

#endif /* TEST */
