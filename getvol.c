/*
**  GETVOL.C - Retrieve a disk volume label
**             (proof you don't need FCBs to do it!)
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <io.h>

#if defined(__TURBOC__)
 #pragma option -a-
 #include <dir.h>
 #define _dos_findfirst(f,a,b) findfirst(f,b,a)
 #define _dos_findnext(b) findnext(b)
 #define find_t ffblk
 #define _A_VOLID FA_LABEL
 #define attrib ff_attrib
 #define name ff_name
#else
 #include <direct.h>
 #if defined(__ZTC__)
  #pragma ZTC align 1
 #else /* MSC/QC/WATCOM/METAWARE */
  #pragma pack(1)
 #endif
#endif

#define SUCCESS 0

char *getvol(char drive)
{
      char search[] = "A:\\*.*";
      static struct find_t ff;

      *search = drive;
      if (SUCCESS == _dos_findfirst(search, _A_VOLID, &ff))
      {
            if (8 < strlen(ff.name))            /* Eliminate period     */
                  strcpy(&ff.name[8], &ff.name[9]);
            return ff.name;
      }
      else  return NULL;
}

#ifdef TEST

int main(int argc, char *argv[])
{
      char *label;

      if (2 > argc)
      {
            puts("\aUsage: GETVOL d[:]");
            puts("where: d = drive letter (e.g. A, B, C, etc.");
            return -1;
      }
      if (NULL == (label = getvol(*argv[1])))
            printf("Unable to read a label on drive %c:\n", *argv[1]);
      else  printf("The volume label of drive %c: is \"%s\"\n",
            *argv[1], label);
      return 0;
}

#endif
