/*
**  FLOPCOPY.C
**
**  Copy a floppy to a hard disk directory with directory recursion
**  Public domain, uses functions from SNIPPETS.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <io.h>
#include <fcntl.h>

#ifdef __TURBOC__
 #include <dir.h>
 #include <dos.h>
 #define _dos_findfirst(f,a,b) findfirst(f,b,a)
 #define _dos_findnext(b) findnext(b)
 #define find_t ffblk
 #define _A_SUBDIR FA_DIREC
 #define attrib ff_attrib
 #define name ff_name
#else
 #include <direct.h>
 #ifdef __ZTC__
  #include <dos.h>
  #ifndef _A_SUBDIR
   #define _A_SUBDIR FA_DIREC
  #endif
 #else                   /* assume MSC/QC                                */
  #include <dos.h>
  #include <errno.h>
  #include <sys\types.h>
 #endif
#endif

#include <sys\stat.h>

#undef SUCCESS
#define SUCCESS 0

#undef NUL
#define NUL '\0'

#define LAST_CHAR(s) (((char *)s)[strlen(s) - 1])

int file_copy(char *,char *);                   /* In Wb_Fcopy.C  */
void do_dir(char *, char *);

/*
**  Copy a floppy to an HD subdirectory
*/

int main(int argc, char *argv[])
{
      char fdrv[4] = "A:\\", target[FILENAME_MAX];

      if (3 > argc)
      {
            puts("Usage: FLOPCOPY drive_letter subdir");
            puts("where: drive_letter is \"A\" or \"B\" (colon optional)");
            puts("       subdir is drive:dir target, e.g. \"C:\\FLOPSTUF\"");
            return EXIT_FAILURE;
      }
      *fdrv = *argv[1];
      strcpy(target, argv[2]);
      if ('\\' != LAST_CHAR(target))
            strcat(target, "\\");
      
      do_dir(fdrv, target);
}

/*
**  Process a directory (SNIPPETS: Treedir.C, modified)
*/

void do_dir(char *from, char *to)
{
      char search[FILENAME_MAX], new[FILENAME_MAX], newto[FILENAME_MAX];
      struct find_t ff;

      strcat(strcpy(search, from), "*.*");
      if (SUCCESS == _dos_findfirst(to, 0xff, &ff))
      {
            if (0 == (ff.attrib & _A_SUBDIR))
            {
                  printf("*** %s Exists and is not a directory!\n", to);
                  return;
            }
      }
      else
      {
            strcpy(newto, to);
            if ('\\' == LAST_CHAR(newto))
                  LAST_CHAR(newto) = NUL;
            mkdir(newto);
      }
      if (SUCCESS == _dos_findfirst(search, 0xff, &ff)) do
      {
            if (ff.attrib & _A_SUBDIR && '.' != *ff.name)
            {
                  strcat(strcat(strcpy(new, from), ff.name), "\\");
                  strcat(strcat(strcpy(newto, to), ff.name), "\\");
                  do_dir(new, newto);
            }
            else
            {
                  char file1[FILENAME_MAX], file2[FILENAME_MAX];

                  if ((ff.attrib & (_A_SUBDIR | _A_VOLID)) || '.' == *ff.name)
                        continue;
                  strcat(strcpy(file1, from), ff.name);
                  strcat(strcpy(file2, to), ff.name);
                  if (SUCCESS != file_copy(file1, file2))
                        printf("*** Unable to copy %s to %s\n", file1, file2);
                  else  printf("Copied %s to %s\n", file1, file2);
            }
      } while (SUCCESS == _dos_findnext(&ff));
}
