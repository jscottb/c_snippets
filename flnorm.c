/*
**  FLNORM.C - Normalize DOS file names
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
#ifdef __TURBOC__
 #include <dir.h>
#else
 #include <direct.h>
#endif
#include <dos.h>
#include <io.h>

#define MAX_FLEN 67
#define LAST_CHAR(string) (((char *)string)[strlen(string)-1])

typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

/*
**  NOTE: Uses the following functions, also in SNIPPETS!
*/

int chdrv(int);                           /* In DRVALID.C   */
char *unix2dos(char *);                   /* In UNIX2DOS.C  */
char *fln_fix(char *);                    /* In FLN_FIX.C   */

int flnorm(char *in_name, char *out_name)
{
      LOGICAL dir_flag = FALSE, new_drv = FALSE, root_flag;
      int status = 0, level = 0;
      char *p, *out;
      static char drive[2][3];
      static char file[14];
      static char I_am_here[MAX_FLEN];
      static char I_am_there[MAX_FLEN];
      static char remember[MAX_FLEN];

      getcwd(I_am_here, MAX_FLEN);
      if (!in_name || !in_name[0])
      {
            strcpy(out_name, I_am_here);
            goto ERRexit;
      }
      strncpy(drive[0], I_am_here, 2);
      drive[0][2] = '\0';
      if (':' == in_name[1])
      {     /* If a drive is specified                            */
            if (chdrv(in_name[0]))
            {     /* If the drive is invalid                      */
                  status = ERROR;
                  goto ERRexit;
            }
            new_drv = TRUE;
            getcwd(remember, MAX_FLEN);
            strncpy(drive[1], remember, 2);
            drive[1][2] = '\0';
      }
      else
      {     /* If a drive isn't specified                         */
            if (NULL != (p = strchr(in_name, ':')))
            {     /* If filename is illegal                       */
                  status = ERROR;
                  goto ERRexit;
            }
      }
      unix2dos(in_name);
      if (new_drv)
      {
            if ('\\' == in_name[2])
                  strcpy(out_name, drive[1]);
            else
            {
                  strcpy(out_name, remember);
                  if ('\\' != LAST_CHAR(remember))
                        strcat(out_name, "\\");
            }
      }
      else
      {
            strcpy(out_name, drive[0]);
            if ('\\' != *in_name)
            {
                  strcat(out_name, I_am_here);
                  if ('\\' != LAST_CHAR(I_am_here))
                        strcat(out_name, "\\");
            }
      }
      strcat(out_name, &in_name[(new_drv) ? 2 : 0]);
      fln_fix(out_name);
      out = &out_name[2];
      if (!(*out))
            goto ERRexit;
      while ('\\' == LAST_CHAR(out))
      {     /* Strip trailing `\'s                                */
            LAST_CHAR(out_name) = '\0';
            dir_flag = TRUE;
      }
      if (!(*out))
      {
            if (dir_flag)
            {
                  strcat(out, "\\");
                  goto ERRexit;
            }
            else  goto BADPATH;
      }
      if (NULL != (p = strrchr(out_name, '\\')))
            strcpy(file, p);        /* Save filename              */
      if (chdir(out))
      {     /* If can't move to path                              */
            if ((!dir_flag) && p)
            {     /* If there was a separate path                 */
                  *p = '\0';
                  if (!(*out))
                  {     /* Back at the root, handle it            */
                        strcpy(p, "\\");
                        strcpy(file, &file[1]);
                  }
                  if (chdir(out))
                  {     /* If we can't move to path               */
                        *p = '\\';
                        goto BADPATH;
                  }
                  ++level;          /* Flag we stripped name      */
            }
            else
            {     /* No path as specified                         */
                  if (p)
                  {
BADPATH:                status = ERROR;
                        goto ERRexit;
                  }
            }
      }
      getcwd(I_am_there, MAX_FLEN); /* Get normalized path        */
      strupr(I_am_there);
      strcpy(out_name, I_am_there);
      if (level)
            strcat(out_name, file);
ERRexit:
      if (new_drv)
      {
            chdir(remember);
            chdrv(I_am_here[0]);
      }
      chdir(I_am_here);
      if (status)
            out_name[0] = '\0';
      return status;
}
