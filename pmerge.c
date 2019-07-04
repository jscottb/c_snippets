/*
**  pmerge() - Portable replacement for fnmerge(), _makepath(), etc.
**
**  Forms a full DOS pathname from drive, path, file, and extension
**  specifications.
**
**  Arguments: 1 - Buffer to receive full pathname
**             2 - Drive
**             3 - Path
**             4 - Name
**             5 - Extension
**
**  Returns: Nothing
**
**  public domain by Bob Stout
*/

#include <string.h>

#define LAST_CHAR(s) ((s)[strlen(s) - 1])

void pmerge(char *path, char *drive, char *dir, char *fname, char *ext)
{
      *path = '\0';

      if (drive && *drive)
      {
            strcat(path, drive);
            if (':' != LAST_CHAR(path))
                  strcat(path, ":");
      }

      if (dir && *dir)
      {
            char *p;

            strcat(path, dir);
            for (p = path; *p; ++p)
                  if ('/' == *p)
                        *p = '\\';
            if ('\\' != LAST_CHAR(path))
                  strcat(path, "\\");
      }

      if (fname && *fname)
      {
            strcat(path, fname);

            if (ext && *ext)
            {
                  if ('.' != *ext)
                        strcat(path, ".");
                  strcat(path, ext);
            }
      }
}

#ifdef TEST

#include <stdio.h>

int main(int argc, char *argv[])
{
      char pathname[FILENAME_MAX];

      pmerge(pathname, argv[1], argv[2], argv[3], argv[4]);
      printf("pmerge (%s, %s, %s, %s) returned:\n %s\n",
            argv[1], argv[2], argv[3], argv[4], pathname);
}
