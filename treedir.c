/*
**  TREEDIR.C - simple recursive directory lister
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <string.h>

#ifdef __ZTC__
 #include <dos.h>
 #ifndef _A_SUBDIR
  #define _A_SUBDIR FA_DIREC
 #endif
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

#ifndef SUCCESS
 #define SUCCESS 0
#endif

void do_dir(char *path)
{
        char search[67], new[67];
        struct find_t ff;

        strcat(strcpy(search, path), "\\*.*");
        if (SUCCESS == _dos_findfirst(search, 0xff, &ff)) do
        {
                printf("%s\\%s\n", path, ff.name);
                if (ff.attrib & _A_SUBDIR && '.' != *ff.name)
                {
                        strcat(strcat(strcpy(new, path), "\\"), ff.name);
                        do_dir(new);
                }
        } while (SUCCESS == _dos_findnext(&ff));
}

void main(void)         /* simple resursive current directory lister    */
{
        do_dir(".");
}
