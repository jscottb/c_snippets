/*
** LSD - A simple directory lister
** A public domain C demo program by Bob Stout
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
 
/* For portability, make everything look like MSC 6+ */
 
#if defined(__TURBOC__)
 #include <dir.h>
 #define _dos_findfirst(f,a,b) findfirst(f,b,a)
 #define _dos_findnext(b) findnext(b)
 #define find_t ffblk
 #define _A_SUBDIR FA_DIREC
 #define attrib ff_attrib
 #define name ff_name
 #define size ff_fsize
 #define wr_time ff_ftime
 #define wr_date ff_fdate
 #define _dos_getdiskfree getdfree
 #define diskfree_t dfree
 #define avail_clusters df_avail
 #define sectors_per_cluster df_sclus
 #define bytes_per_sector df_bsec
#else                                     /* assume MSC/QC              */
 #include <errno.h>
#endif
 
#ifdef TRUE
 #undef TRUE
#endif
#ifdef FALSE
 #undef FALSE
#endif
#ifdef ERROR
 #undef ERROR
#endif
 
enum LOGICAL {ERROR = -1, SUCCESS, FALSE = 0, TRUE};
 
#ifndef CAST
 #define CAST(new_type,old_object) (*((new_type *)&(old_object)))
#endif
 
#define LAST_CHAR(s) (((char *)s)[strlen(s) - 1])
 
struct DOS_TIME {
        unsigned int ss : 5;
        unsigned int mm : 6;
        unsigned int hh : 5;
        } ;
#define dos_time(t) CAST(struct DOS_TIME, (t))
 
struct DOS_DATE {
        unsigned int da : 5;
        unsigned int mo : 4;
        unsigned int yr : 7;
        } ;
#define dos_date(t) CAST(struct DOS_DATE, (t))
 
/*
**  DOS DIR improved work-alike w/ improved formatting & attribute display
**
**  supports /W switch
*/
 
main(int argc, char *argv[])
{
      int i, files = 0, dirs = 0, argptr = 0, errflag = FALSE, cols, drive;
      long siz_tot = 0L;
      char *p, *fname, *ext, name[13], buf[67], numbuf[12];
      struct find_t ff;
#ifndef __ZTC__
      struct diskfree_t df;
#endif
      int one_column(), five_column();
      int (*display)(char *, char *, long, unsigned, unsigned, unsigned)
            = one_column;
      char *sprintfc(char *, long);
      char *capitalize(const char *);
 
      strcpy(buf, fname = "*.*");
      if(argc != 1)   for (i = 1; i < argc; ++i)
      {
            if ('/' == argv[i][0])
            {
                  if ('W' == toupper(argv[i][1]))
                        display = five_column;
                  else
                  {
                        puts("\aUsage: LSD [/W] [file]");
                        errflag = TRUE;
                  }
            }
            else if (!argptr)
                  argptr = i;
      }
      if (argptr)
      {
            fname = argv[argptr];
            strcpy(buf, fname);
            if ('\\' == LAST_CHAR(buf) || ':' == LAST_CHAR(buf))
                  strcat(buf, "*.*");
            else
            {
                  if (SUCCESS == _dos_findfirst(buf, _A_SUBDIR, &ff))
                  {
                        if (ff.attrib & _A_SUBDIR && '.' != *ff.name)
                        {
                              if ('\\' != LAST_CHAR(buf))
                                    strcat(buf, "\\");
                              strcat(buf, "*.*");
                        }
                  }
                  else  errflag = TRUE;
            }
      }
      if (':' == buf[1])
            drive = toupper(*buf) - '@';
      else  drive = 0;
      if (!errflag && !(_dos_findfirst(buf, 0xff, &ff))) do
      {
            siz_tot += ff.size;
            if (ff.attrib & _A_SUBDIR)
                  ++dirs;
            else  ++files;
            strcpy(name, ff.name);
            if (NULL != (p = strchr(name, '.')) && p != name)
            {
                  *p  = '\0';
                  ext = ++p;
            }
            else  ext = "";
            cols = (*display)(name, ext, ff.size,
                  ff.attrib, ff.wr_date, ff.wr_time);
      } while (SUCCESS == _dos_findnext(&ff));
      else
      {
            fprintf(stderr, "Cannot do directory on '%s'\n", fname);
            exit(-1);
      }
      if (cols)
            fputc('\n', stdout);
      sprintfc(numbuf,siz_tot);
      printf("\n%3d Files totalling %s bytes\n", files, numbuf);
      printf("%3d Director%s\n", dirs, (1 == dirs) ? "y" : "ies");
#ifndef __ZTC__
      _dos_getdiskfree(drive, &df);
      sprintfc(numbuf, (long)df.avail_clusters * df.sectors_per_cluster *
            df.bytes_per_sector);
#else /* if ZTC */
      sprintfc(numbuf, dos_getdiskfreespace(drive));
#endif
      printf("%s bytes free\n", numbuf);
      return 0;
}
 
/*
**  The single column directory entry display function
*/
 
int one_column(char    *name,
               char    *ext,
               long     size,
               unsigned attribs,
               unsigned date,
               unsigned time)
{
      register int i, mask;
      static char *atr = "RHSVDA", szbuf[12];
 
      sprintfc(szbuf, size);
      printf("%-8s %-3s %12s  ", capitalize(name), capitalize(ext), szbuf);
      for (i = 0, mask = 1; i < 6; ++i, mask <<= 1)
      {
            if (attribs & mask)
                  fputc(atr[i], stdout);
            else  fputc('.'   , stdout);
      }
      printf("%4d-%02d-%02d%4d:%02d:%02d\n",
            dos_date(date).mo,
            dos_date(date).da,
            (dos_date(date).yr + 80) % 100,
            dos_time(time).hh,
            dos_time(time).mm,
            dos_time(time).ss);
      return 0;
}
 
/*
**  The five column directory entry display function
*/
 
int five_column(char    *name,
                char    *ext,
                long     size,
                unsigned attribs,
                unsigned date,
                unsigned time)
{
      static int cols = 0;

      printf("%-8s %-3s%s", capitalize(name), capitalize(ext),
            (5 > ++cols) ? "    " : "");
      if (0 == (cols %= 5))
            putchar('\n');
      return (cols);
}
 
/*
**  Display a long int using commas as thousands separators
*/
 
char *sprintfc(char *string, long num)
{
      if (num > 999999L)
      {
            sprintf(string, "%d,%03d,%03d",
                  (int)(num / 1000000L),
                  (int)((num % 1000000L) / 1000L),
                  (int)(num % 1000L));
      }
      else
      {
            if (num > 999L)
            {
                  sprintf(string, "%d,%03d",
                        (int)(num / 1000L),
                        (int)(num % 1000L));
            }
            else  sprintf(string, "%d", (int)num);
      }
      return string;
}
 
/*
**  Capitalize a name or extension in place
*/
 
char *capitalize(const char *string)
{
      int flag = 0;
      char *ptr = (char *)string;
 
      do
      {
            if (isalpha(*ptr))
            {
                  if (flag)
                        *ptr = (char)tolower(*ptr);
                  else
                  {
                        flag = 1;
                        *ptr = (char)toupper(*ptr);
                  }
            }
            else  flag = 0;
      } while (*++ptr);
      return (char *)string;
}
