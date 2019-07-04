/*
**  FLN_FIX.C
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <io.h>

#define LAST_CHAR(string) (((char *)string)[strlen(string)-1])

typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

char *unix2dos(char *path);

/****************************************************************/
/*                                                              */
/*  Function to `crunch' dot directories and check for          */
/*  DOS-valid path strings. Drive specifiers in the path        */
/*  ignored.                                                    */
/*                                                              */
/****************************************************************/

char *fln_fix(char *path)
{
      LOGICAL dir_flag = FALSE, root_flag = FALSE;
      char *r, *p, *q, *s;

      if (path)
            strupr(path);

      /* Ignore leading drive specs   */

      if (NULL == (r = strrchr(path, ':')))
            r = path;
      else  ++r;

      unix2dos(r);                      /* Convert Unix to DOS style    */

      while ('\\' == *r)                /* Ignore leading backslashes   */
      {
            if ('\\' == r[1])
                  strcpy(r, &r[1]);
            else
            {
                  root_flag = TRUE;
                  ++r;
            }
      }

      p = r;                            /* Change "\\" to "\"           */
      while (NULL != (p = strchr(p, '\\')))
      {
            if ('\\' ==  p[1])
                  strcpy(p, &p[1]);
            else  ++p;
      }

      while ('.' == *r)                 /* Scrunch leading ".\"         */
      {
            if ('.' == r[1])
            {
                  /* Ignore leading ".."                                */

                  for (p = (r += 2); *p && (*p != '\\'); ++p)
                        ;
            }
            else
            {
                  for (p = r + 1 ;*p && (*p != '\\'); ++p)
                        ;
            }
            strcpy(r, p + ((*p) ? 1 : 0));
      }

      while ('\\' == LAST_CHAR(path))   /* Strip trailing backslash     */
      {
            dir_flag = TRUE;
            LAST_CHAR(path) = '\0';
      }

      s = r;

      /* Look for "\." in path        */

      while (NULL != (p = strstr(s, "\\.")))
      {
            if ('.' == p[2])
            {
                  /* Execute this section if ".." found                 */

                  q = p - 1;
                  while (q > r)           /* Backup one level           */
                  {
                        if (*q == '\\')
                              break;
                        --q;
                  }
                  if (q > r)
                  {
                        strcpy(q, p + 3);
                        s = q;
                  }
                  else if ('.' != *q)
                  {
                        strcpy(q + ((*q == '\\') ? 1 : 0),
                              p + 3 + ((*(p + 3)) ? 1 : 0));
                        s = q;
                  }
                  else  s = ++p;

            }
            else
            {
                  /* Execute this section if "." found                  */

                  q = p + 2;
                  for ( ;*q && (*q != '\\'); ++q)
                        ;
                  strcpy (p, q);
            }
      }

      if (root_flag)  /* Embedded ".." could have bubbled up to root  */
      {
            for (p = r; *p && ('.' == *p || '\\' == *p); ++p)
                  ;
            if (r != p)
                  strcpy(r, p);
      }

      if (dir_flag)
            strcat(path, "\\");
      return path;
}
