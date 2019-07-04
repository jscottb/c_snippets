/*
**  CANT.C - An fopen() replacement with error trapping
**
**  public domain by Bob Stout
**
**  Call just as you would fopen(), but make sure your exit functions are
**  registered with atexit().
*/

#include <stdio.h>

FILE *cant(char *fname, char *fmode)
{
      FILE *fp;

      if (NULL == (fp = fopen(fname, mode)))
      {
            fprintf(stderr, "Can't open %s\n", fname);
            exit(EXIT_FAILURE);
      }
      return fp;
}
