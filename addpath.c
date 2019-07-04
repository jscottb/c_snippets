/*
**  Append a new directory to the AUTOEXEC.BAT path
**
**  public domain by Bob Stout
**  also uses TRIM.C from SNIPPETS
*/

#include <stdio.h>
#include <string.h>

char *trim(char *);

#define TAG_1 "set path="
#define TAG_2 "path="

typedef enum {ERROR = -1, SUCCESS} LOGICAL;

#define NUL '\0'
#define LAST_CHAR(s) (((char *)s)[strlen(s) - 1])

#ifdef TESTDIR
 #define ROOT ""        /* While testing, do things in the current dir  */
#else
 #define ROOT "\\"      /* Otherwise, look for AUTOEXEC.BAT in the root */
#endif

LOGICAL addpath(char *newdir)
{
      FILE *autoexec, *tmp;
      char fname[FILENAME_MAX], bakname[FILENAME_MAX];
      char tfname[L_tmpnam], tbakname[L_tmpnam];
      char *ptr;

      strcat(strcpy(fname, ROOT), "autoexec.bat");
      tmpnam(tfname);
      tmpnam(tbakname);

      strcpy(bakname, fname);
      if (NULL != (ptr = strrchr(bakname, '.')))
      {
            if (NULL == strchr(ptr, '\\') && NULL == strchr(ptr, '/'))
                  *ptr = NUL;
      }
      strcat(bakname, ".bak");

      rename(bakname, tbakname);
      rename(fname, bakname);

      if (NULL == (autoexec = fopen(bakname, "r")))
      {
            if (NULL == (autoexec = fopen(fname, "w")))
                  return ERROR;
            fprintf(autoexec, "SET PATH=%s\n", newdir);
            fclose(autoexec);
            remove(tbakname);
            return SUCCESS;
      }
      if (NULL == (tmp = fopen(tfname, "w")))
      {
            fclose(autoexec);
            rename(bakname, fname);
            rename(tbakname, bakname);
            return ERROR;
      }
      else  remove(tbakname);

      while (!feof(autoexec))
      {
            char rline[256 + FILENAME_MAX];
            char tline[256 + FILENAME_MAX];

            if (fgets(rline, 256, autoexec))
            {
                  trim(strcpy(tline, rline));
                  if ((SUCCESS == strnicmp(tline, TAG_1, strlen(TAG_1))) ||
                        (SUCCESS == strnicmp(tline, TAG_2, strlen(TAG_2))))
                  {
                        if ('\n' == LAST_CHAR(rline))
                              LAST_CHAR(rline) = NUL;
                        strcat(rline, (';' == LAST_CHAR(rline) ? "" : ";"));
                        strcat(strcat(rline, newdir), "\n");
                  }
                  fputs(rline, tmp);
            }
      }

      fclose(autoexec);
      fclose(tmp);

      rename(tfname, fname);
      return SUCCESS;
}

#ifdef TEST

main()
{
      printf("addpath(mydir) returned %d\n", addpath("mydir"));
}

#endif
