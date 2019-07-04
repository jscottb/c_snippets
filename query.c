/*
**  QUERY.C - Timed query with default for batch files
**
**  public domain by Bob Stout
*/

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

main(int argc, char *argv[])
{
      int ch = '\0', def_ch = '\0';
      char *prompt = "(y/n) ";
      clock_t start, limit = (clock_t)0;

      if (1 < argc)
      {
            def_ch = toupper(*argv[1]);
            if ('Y' == def_ch)
                  prompt[1] = (char)def_ch;
            else if ('N' == def_ch)
                  prompt[3] = (char)def_ch;
            else  def_ch = '\0';
      }
      fputs(prompt, stderr);
      if (2 < argc)
      {
            start = clock();
            limit = (clock_t)(CLK_TCK * atoi(argv[2]));
      }
      while ('Y' != ch && 'N' != ch)
      {
            while (!kbhit())
            {
                  if (limit && (limit <= (clock() - start)))
                  {
                        ch = def_ch;
                        goto BYE;
                  }
            }
            ch = toupper(getch());
            if ('Y' != ch && 'N' != ch && (1 < argc))
                  ch = def_ch;
      };
BYE:  fputc(ch, stderr);
      fputc('\n', stderr);
      return ('Y' == ch);
}
