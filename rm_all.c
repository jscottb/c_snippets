/*
**  Remove all files and (optionally) subdirectories
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <dos.h>
#include <ctype.h>

#define LAST_CHAR(str) (str[strlen(str) - 1])
#define MAX_PATH 80

#ifdef __TURBOC__
 #include <dir.h>
 #include <io.h>
 #define FAR far
 #define find_1st(n,a,b) (findfirst((n),(b),(a)))
 #define find_nxt(b) (findnext(b))
 #define find_t ffblk
 #define name ff_name
 #define attrib ff_attrib
 #define _A_SUBDIR FA_DIREC
#else
 #include <direct.h>
 #include <stdarg.h>
 #define FAR _far
 #define find_1st(n,a,b) (_dos_findfirst((n),(a),(b)))
 #define find_nxt(b) (_dos_findnext(b))

 #ifndef FA_RDONLY
  #define FA_RDONLY _A_RDONLY
 #endif

 #ifndef FA_HIDDEN
  #define FA_HIDDEN _A_HIDDEN
 #endif

 #ifndef FA_SYSTEM
  #define FA_SYSTEM _A_SYSTEM
 #endif

 #if (defined(_MSC_VER) && (_MSC_VER >= 700)) || (defined(__SC__))
  // Make FP_xxx macros lvalues as in older versions
  #undef FP_SEG
  #undef FP_OFF
  #define FP_SEG(fp)    ((unsigned)((unsigned long)(fp) >> 16))
  #define FP_OFF(fp)    ((unsigned)(fp && 0xffff))
 #endif

#endif

/* Select one of the following - remove() is ANSI       */

#define rmfunc remove
/* #define rmfunc unlink */

#define show(s) fputs((s), stderr)

typedef enum {ERROR = -1, SUCCESS, FALSE = 0, TRUE} LOGICAL;
LOGICAL recurse = FALSE, gobble = FALSE, ignore = FALSE;

char *mask = "*.*";

/*
**  Clean all files from a directory
*/

void clean_dir(char *path)
{
      char rmpath[MAX_PATH], *rmfile;
      struct find_t fbuf;
      unsigned attrib = (ignore) ? 0xff : 0;

      strcpy(rmpath, path);
      if ('\\' != LAST_CHAR(rmpath))
            strcat(rmpath, "\\");
      rmfile = &rmpath[strlen(rmpath)];
      strcpy(rmfile, mask);
      if (0 == find_1st(rmpath, attrib, &fbuf)) do
      {
            strcpy(rmfile, fbuf.name);
            if (ignore)
            {
                  union REGS regs;
                  struct SREGS sregs;

                  regs.x.ax = 0x4300;
                  regs.x.dx = FP_OFF((char FAR *)rmpath);
                  segread(&sregs);
                  sregs.ds  = FP_SEG((char FAR *)rmpath);
                  intdosx(&regs, &regs, &sregs);
                  if (!regs.x.cflag)
                  {
                        regs.x.ax  = 0x4301;
                        regs.x.cx &= ~(FA_RDONLY | FA_HIDDEN | FA_SYSTEM);
                        intdosx(&regs, &regs, &sregs);
                        if (regs.x.cflag)
                              printf("unable to delete %s\n", rmpath);
                  }
            }
            rmfunc(rmpath);
            printf("deleting %s\n", rmpath);
      } while (0 == find_nxt(&fbuf));
}

/*
**  Process directories
*/

void do_dir(char *path)
{
      char search[MAX_PATH], new[MAX_PATH];
      struct find_t ff;

      strcpy(search, path);
      if ('\\' != LAST_CHAR(search))
            strcat(search, "\\");
      strcat(search, "*.*");
      if (SUCCESS == find_1st(search, 0xff, &ff)) do
      {
            if (ff.attrib & _A_SUBDIR && '.' != *ff.name)
            {
                  strcpy(new, path);
                  if ('\\' != LAST_CHAR(new))
                        strcat(new, "\\");
                  strcat(new, ff.name);
                  do_dir(new);
            }
      } while (SUCCESS == find_nxt(&ff));
      clean_dir(path);
      if (gobble)
            rmdir(path);
}

/*
**  Tell 'em they messed up
*/

void usage(LOGICAL errstat)
{
      if (errstat)
            fputc('\a', stderr);
      show("Usage: RM_ALL directory [...directory] [-eFNAME.EXT] [-rgi?]\n");
      show("switches: -eFNAME.EXT  Remove only files matching mask "
            "(default is \"-e*.*\")\n");
      show("          -r           Recurse subdirectories\n");
      show("          -g           Gobble (delete) empty subdirectories\n");
      show("          -i           Ignore special file attributes "
            "(CAUTION!)\n");
      show("          -?           Display help (this message)\n");
      exit(errstat);
}

/*
**  RM_ALL - Deletes all files and (optionally) subdirectories
*/

int main(int argc, char *argv[])
{
      int i, j;
      LOGICAL found_dir = FALSE;
      void (*clean_func)(char *) = clean_dir;

      for (i = 1; i < argc; ++i)          /* Check for switches         */
      {
            if (NULL == strchr("-/", *argv[i]))
                  continue;               /* Assume it's a filename     */
            for (j = 1; argv[i][j] ; ++j) /* Traverse nested switches   */
            {
                  switch (toupper(argv[i][j]))
                  {
                  case 'R':
                        clean_func = do_dir;
                        break;

                  case 'G':
                        gobble = TRUE;
                        break;

                  case 'I':
                        ignore = TRUE;
                        break;

                  case '?':
                        puts("***help***");
                        usage(FALSE);
                        break;

                  case 'E':
                        if (0 == strlen(&argv[i][++j]))
                        {
                              puts("***no file***");
                              usage(ERROR);                 /* Oops     */
                        }
                        mask = strupr(&argv[i][j]);
                        j += strlen(&argv[i][j]) - 1; /* End of switch  */
                        break;

                  default:
                        puts("***default***");
                        usage(ERROR);
                  }
            }
      }
      for (i = 1; i < argc; ++i)          /* Scan filenames             */
      {
            if (strchr("/-", *argv[i]))
                  continue;
            found_dir = TRUE;
            clean_func(argv[i]);
      }
      if (!found_dir)
      {
            puts("***not found***");
            usage(TRUE);
      }
      else  return 0;
}
