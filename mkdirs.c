/*
**  MKDIRS.C - Function to build multi-level directories in a single call
**
**  Original Copyright 1993 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __TURBOC__
 #include <dir.h>
#else
 #include <direct.h>
#endif

int mkdirs(char *path)
{
      int retval;

      while (0 != (retval = mkdir(path)))
      {
            char subpath[FILENAME_MAX] = "", *delim;

            if (NULL == (delim = strrchr(path, '\\')))
                  return retval;
            strncat(subpath, path, delim - path);     /* Appends NUL    */
            mkdirs(subpath);
      }
      return retval;
}

#ifdef TEST

main(int argc, char *argv[])
{
      if (2 > argc)
      {
            puts("Usage: MKDIRS pathname [...pathname]");
            return -1;
      }
      while (--argc)
      {
            ++argv;
            printf("mkdirs(%s) returned %d\n", *argv, mkdirs(*argv));
      }
      return 0;
}

#endif /* TEST */
