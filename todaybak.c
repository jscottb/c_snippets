/*
**  TODAYBAK.C - Back up today's work to a specified floppy
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

#if defined(__ZTC__) && (__ZTC__ < 0x600)
 #define _dos_getdate   dos_getdate
 #define _dos_setdate   dos_setdate
 #define _dosdate_t     dos_date_t
#endif
#ifdef __TURBOC__
 #define _dosdate_t     dosdate_t
#endif

#ifndef SUCCESS
 #define SUCCESS 0
#endif
 
#ifndef CAST
 #define CAST(new_type,old_object) (*((new_type *)&(old_object)))
#endif
 
#define LAST_CHAR(s) (((char *)s)[strlen(s) - 1])
 
struct DOS_DATE {
        unsigned int da : 5;
        unsigned int mo : 4;
        unsigned int yr : 7;
        } ;

struct _dosdate_t today;
struct DOS_DATE   ftoday;
char   drive;

void do_dir(char *);
void usage(void);

int main(int argc, char *argv[])
{
      int i;

      _dos_getdate(&today);
      ftoday.da = today.day;
      ftoday.mo = today.month;
      ftoday.yr = today.year - 1980;

      if (2 > argc)
            usage();

      drive = *argv[1];
      if (!strchr("AaBb", drive))
            usage();

      if (3 > argc)
            do_dir(".");
      else for (i = 2; i < argc; ++i)
            do_dir(argv[i]);

      return EXIT_SUCCESS;
}

void usage(void)
{
      puts("usage: TODAYBAK floppy [dir1] [...dirN]");
      puts("       Copies today's files to the specified floppy.");
      puts("       floppy = 'A' | 'B'");
      puts("       with no directories specified, "
            "uses current directory");
      exit(EXIT_FAILURE);
}

void do_dir(char *path)
{
      char search[67];
      struct find_t ff;

      strcat(strcpy(search, path), "\\*.*");
      if (SUCCESS == _dos_findfirst(search, 0xff, &ff)) do
      {
            if (!(ff.attrib & _A_SUBDIR) && '.' != *ff.name)
            {
                  if (ff.wr_date == CAST(unsigned short, ftoday))
                  {
                        char cmd[128];

                        sprintf(cmd, "COPY %s\\%s %c: > NUL",
                              path, ff.name, drive);
                        system(cmd);
                  }
            }
      } while (SUCCESS == _dos_findnext(&ff));
}
