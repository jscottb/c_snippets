/*
** Apologies for the grotty code; I only just whipped this up.
**
** tname.c -- wrapper for the undocumented DOS function TRUENAME
**
** TRUENAME: interrupt 0x21 function 0x60
**
**   Call with: ah    =  60h
**              es:di -> destination buffer
**              ds:si -> source buffer
**
**   Returns:   carry bit set if there were problems
**
** This code hereby contributed to the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>

#ifdef __TURBOC__
 #define _far far
#endif

/*
** Strip leading and trailing blanks from a string.
*/

char _far *strip(char _far *s)
{
      char _far *end;

      for ( ; isspace(*s); s++)
            ;

      for (end = s; *end; end++)
            ;

      for (end--; isspace(*end); *end-- = '\0')
            ;

      return s;
}

/*
** Truename itself. Note that I'm using intdosx() rather than
** playing with some inline assembler -- I've discovered some
** people that actually don't have an assembler, poor bastards :-)
*/

char _far *truename(char _far *dst, char _far *src)
{
      union REGS rg;
      struct SREGS rs;

      if (!src || !*src || !dst)
            return NULL;

      src=strip(src);

      rg.h.ah=0x60;
      rg.x.si=FP_OFF(src);
      rg.x.di=FP_OFF(dst);
      rs.ds=FP_SEG(src);
      rs.es=FP_SEG(dst);

      intdosx(&rg,&rg,&rs);

      return (rg.x.cflag) ? NULL : dst;
}

#ifdef TEST

/*
** ... and a little test function.
*/

int main(int argc, char *argv[])
{
      char buf[128]="                             ", _far *s;
      int i;

      if (3 > _osmajor)
      {
            puts("Only works with DOS 3+");
            return -1;
      }
      if(argc > 1)
      {
            for(i = 1; i < argc; i++)
            {
                  s = truename((char _far *)buf,(char _far *)argv[i]);
                  printf("%s=%s\n",argv[i], s ? buf : "(null)");
            }
      }
      else  printf("Usage: TRUENAME [filename [filename...]]\n");

      return 0;
}

#endif
