/*
**  FILCOUNT.C - counts directories and /or files in a directory
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <string.h>

#undef TRUE
#undef FALSE
typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

#ifdef __ZTC__
 #include <dos.h>
#elif defined(__TURBOC__)
 #include <dir.h>
 #include <dos.h>
 #define _dos_findfirst(f,a,b) findfirst(f,b,a)
 #define _dos_findnext(b) findnext(b)
 #define find_t ffblk
 #define _A_SUBDIR FA_DIREC
 #define attrib ff_attrib
 #define name ff_name
#else                   /* assume MSC/QC                                */
 #include <dos.h>
 #include <errno.h>
#endif

#undef SUCCESS
#define SUCCESS 0

#define LAST_CHAR(str) (str)[strlen(str) - 1]

unsigned DirCount = 0, FileCount = 0;

/*
**  Arguments: 1 - directory to search
**             2 - search subdirectories: TRUE or FALSE
*/

void do_dir(char *path, int recurse_flag)
{
      char search[67], new[67];
      struct find_t ff;

      strcpy(search, path);
      if ('\\' != LAST_CHAR(search))
            strcat(search, "\\");
      strcat(search, "*.*");
      if (SUCCESS == _dos_findfirst(search, 0xff, &ff)) do
      {
            if ('.' == *ff.name)
                  continue;
            if (ff.attrib & _A_SUBDIR)
            {
                  DirCount++;
                  if (recurse_flag)
                  {
                        strcpy(new, path);
                        if  ('\\' != LAST_CHAR(new))
                              strcat(new, "\\");
                        strcat(new, ff.name);
                        do_dir(new, recurse_flag);
                  }
            }
            else  FileCount++;
      } while (SUCCESS == _dos_findnext(&ff));
}

/*
**  Simple resursive file/directory counter
**
**  Usage: FILCOUNT [path_name] [{Y | N}]
**
**  Notes: 1. If a path name isn't specified, the current directory is assumed
**         2. Default recursion flag is FALSE
**         3. Path must be specified in order to specify the recursion flag
*/

void main(int argc, char *argv[])
{
      char *Dir =".";
      LOGICAL recurse = FALSE;

      if (1 < argc)
            Dir = argv[1];
      if (2 < argc)
            recurse = (NULL != strchr("Yy", *argv[2]));
      do_dir(Dir, recurse);
      printf("Counted: %d Directories and %d Files\n",
              DirCount, FileCount);
}
