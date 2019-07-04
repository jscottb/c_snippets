/*
** LSARY - A simple directory lister using a filename array
** A public domain C demo program by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>

/* For portability, make everything look like MSC 6 */

#if defined(__TURBOC__)
 #include <dir.h>
 #define _dos_findfirst(f,a,b) findfirst(f,b,a)
 #define _dos_findnext(b) findnext(b)
 #define find_t ffblk
 #ifndef _A_SUBDIR
  #define _A_SUBDIR FA_DIREC
 #endif
 #define attrib ff_attrib
 #define name ff_name
 #define size ff_fsize
 #define wr_time ff_ftime
 #define wr_date ff_fdate
 #define _dos_getdiskfree getdfree
 #define diskfree_t dfree
 #define avail_clusters df_avail
 #define sectors_per_cluster df_sclus
 #define bytes_per_sector df_bsec
#else                   /* assume MSC/QC                                */
 #include <errno.h>
#endif

#ifdef TRUE
 #undef TRUE
#endif
#ifdef FALSE
 #undef FALSE
#endif
#ifdef ERROR
 #undef ERROR
#endif

enum LOGICAL {ERROR = -1, SUCCESS, FALSE = 0, TRUE};

#ifndef CAST
 #define CAST(new_type,old_object) (*((new_type *)&(old_object)))
#endif

#define LAST_CHAR(s) (((char *)s)[strlen(s) - 1])

struct DirEntry {
      char fname[FILENAME_MAX];
      struct DirEntry *next;
} DirRoot = {"", NULL};

/*
**  Read a directory into an array
*/

int ReaDirArray(char *path)
{
      struct find_t ff;
      char pattern[67];
      struct DirEntry *base = &DirRoot;

      strcpy(pattern, path);
      if ('/' != LAST_CHAR(pattern) && '\\' != LAST_CHAR(pattern))
            strcat(pattern, "\\");
      strcat(pattern, "*.*");
      if (SUCCESS == _dos_findfirst(pattern, 0xff, &ff)) do
      {
            struct DirEntry *node;

            if (NULL == (node = malloc(sizeof(struct DirEntry))))
                  return ERROR;
            base->next = node;
            strcpy(base->fname, ff.name);
            node->next = NULL;
            *node->fname = '\0';
            base = node;
            
      } while (SUCCESS == _dos_findnext(&ff));
      return SUCCESS;
}

/*
**  Simple directory lister
*/

void main(int argc, char *argv[])
{
      char *path;

      if (2 > argc)
            path = ".";
      else  path = argv[1];
      if (ERROR == ReaDirArray(path))
            printf("*** Could not read %s\n", path);
      else
      {
            struct DirEntry *node = &DirRoot;
            printf("Directory of %s\n\n", path);
            while (node)
            {
                  puts(node->fname);
                  node = node->next;
            }
      }
}
