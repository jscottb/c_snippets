/*
   --------------------------------------------------------------------
   Module:     REPLACE.C
   Author:     Gilles Kohl
   Started:    09.06.1992   12:16:47
   Modified:   09.06.1992   12:41:41
   Subject:    Replace one string by another in a given buffer.
               This code is public domain. Use freely.
   --------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * StrReplace: Replace OldStr by NewStr in string Str.
 *
 * Str should have enough allocated space for the replacement, no check
 * is made for this. Str and OldStr/NewStr should not overlap.
 * The empty string ("") is found at the beginning of every string.
 *
 * Returns: pointer to first location behind where NewStr was inserted
 * or NULL if OldStr was not found.
 * This is useful for multiple replacements, see example in main() below
 * (be careful not to replace the empty string this way !)
 */

char *StrReplace(char *Str, char *OldStr, char *NewStr)
{
      int OldLen, NewLen;
      char *p, *q;

      if(NULL == (p = strstr(Str, OldStr)))
            return p;
      OldLen = strlen(OldStr);
      NewLen = strlen(NewStr);
      memmove(q = p+NewLen, p+OldLen, strlen(p+OldLen)+1);
      memcpy(p, NewStr, NewLen);
      return q;
}

#ifdef TEST

/*
 * Test main().
 * Given two arguments, replaces the first arg. in the lines read from
 * stdin by the second one.
 * Example invocation:
 * replace printf puts <replace.c
 * will replace all printf's by puts in replace's source.
 *
 */

int main(int argc, char *argv[])
{
      char buf[200];
      char *Start;

      if(argc != 3)
            exit(1);

      /* Repeat until all occurences replaced */

      while(NULL != (Start = gets(buf)))
      {
            while(NULL != (Start = StrReplace(Start, argv[1], argv[2])))
                  ;
            printf("%s\n", buf);
      }
      return 0;
}

#endif TEST
