/*
**  psplit() - Portable replacement for fnsplit(), _splitpath(), etc.
**
**  Splits a full DOS pathname into drive, path, file, and extension
**  specifications. Works with forward or back slash path separators and
**  network file names, e.g. NET:LOONEY/BIN\WUMPUS.COM, Z:\MYDIR.NEW/NAME.EXT
**
**  Arguments: 1 - Full pathname to split
**             2 - Buffer for drive
**             3 - Buffer for path
**             4 - Buffer for name
**             5 - Buffer for extension
**
**  Returns: Nothing
**
**  public domain by Bob Stout
*/

#include <stdlib.h>
#include <string.h>

#define NUL '\0'

void psplit(char *path, char *drv, char *dir, char *fname, char *ext)
{
      char ch, *ptr, *p;

      /* convert slashes to backslashes for searching       */

      for (ptr = path; *ptr; ++ptr)
      {
            if ('/' == *ptr)
                  *ptr = '\\';
      }

      /* look for drive spec                                */

      if (NULL != (ptr = strchr(path, ':')))
      {
            ++ptr;
            if (drv)
            {
                  strncpy(drv, path, ptr - path);
                  drv[ptr - path] = NUL;
            }
            path = ptr;
      }
      else if (drv)
            *drv = NUL;
      
      /* find rightmost backslash or leftmost colon         */

      if (NULL == (ptr = strrchr(path, '\\')))
            ptr = (strchr(path, ':'));

      if (!ptr)
      {
            ptr = path;             /* obviously, no path   */
            if (dir)
                  *dir = NUL;
      }
      else
      {
            ++ptr;                  /* skip the delimiter   */
            if (dir)
            {
                  ch = *ptr;
                  *ptr = NUL;
                  strcpy(dir, path);
                  *ptr = ch;
            }
      }

      if (NULL == (p = strrchr(ptr, '.')))
      {
            if (fname)
                  strcpy(fname, ptr);
            if (ext)
                  *ext = NUL;
      }
      else
      {
            *p = NUL;
            if (fname)
                  strcpy(fname, ptr);
            *p = '.';
            if (ext)
                  strcpy(ext, p);
      }
}

#ifdef TEST

#include <stdio.h>

int main(int argc, char *argv[])
{
      char drive[10], pathname[FILENAME_MAX], fname[9], ext[5];

      while (--argc)
      {
            psplit(*++argv, drive, pathname, fname, ext);
            printf("psplit(%s) returns:\n drive = %s\n path  = %s\n"
                  " name  = %s\n ext   = %s\n",
                  *argv, drive, pathname, fname, ext);
      }
      return EXIT_SUCCESS;
}

#endif
