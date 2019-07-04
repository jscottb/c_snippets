/*
**  POSIXDIR.C - POSIX-style directory processing
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>
#include <errno.h>
#include "dirent.h"

#define _NDIRS 20
#define SUCCESS 0
#define ERROR  -1

#define LAST_CHAR(s) ((char *)(s))[strlen(s) - 1]

int DFerr;
DOS_DIR _DIRS[_NDIRS];  /* Initilize DOS_DIR array to zeros     */

/*
**  Convert Unix-style pathnames to DOS-style
*/

static char *unix2dos(char *path)
{
      char *p;

      while (NULL != (p = strchr(path, '/')))
            *p = '\\';
      return path;
}

/****************************************************************/
/*                                                              */
/*  opendir()                                                   */
/*                                                              */
/*  Function: Open a directory for reading.                     */
/*                                                              */
/*  Parameters: 1 - Directory name. May include path spec.      */
/*                                                              */
/*  Returns: Pointer to a DOS_DIR typedef'ed structure, similar */
/*           to fopen() returning a FILE pointer.               */
/*                                                              */
/*           NULL if error, DFerr set as follows:               */
/*           SUCCESS - No error                                 */
/*           ENOENT  - Could not locate directory or contents   */
/*           ENOTDIR - Not a directory                          */
/*           ENOMEM  - Too many directories already open        */
/*                                                              */
/*  Side effects: The dd_size element of the DOS_DIR structure  */
/*                will contain a number representing the total  */
/*                number of entries in the directory. The       */
/*                dd_loc element will be set to zero since      */
/*                no elements have, as yet, been read.          */
/*                                                              */
/****************************************************************/

DOS_DIR *opendir(char *fname)
{
      int i;
      unsigned n = 0;
      char nametmp[13], *p;
      struct DSTRUCT dstruct;

      for (i = 0; i < _NDIRS; ++i)
      {
            if (!_DIRS[i].dd_fd)
                  break;
      }
      if (_NDIRS <= i)
      {
            DFerr = ENOMEM;
            return NULL;
      }

      unix2dos(fname);
      if (':' == fname[1] && 1 < strlen(fname))
            p = &fname[2];
      else  p = fname;
      while ('\\' == LAST_CHAR(p) && 1 < strlen(p))
            LAST_CHAR(p) = '\0';
        
      if (strcmp(p, "\\") && strlen(p))
      {
            if (NULL == (rfind_1st(fname, FA_ANY, &_DIRS[i].dd_buf)))
            {
                  DFerr = ENOENT;
                  return NULL;
            }
            if (!(FA_DIREC & _DIRS[i].dd_buf.ATTRIBUTE))
            {
                  DFerr = ENOTDIR;
                  return NULL;
            }
      }
      strcpy(_DIRS[i].dd_dirname, fname);
      if (!strlen(p))
            strcat(_DIRS[i].dd_dirname, ".");
      if ('\\' != LAST_CHAR(_DIRS[i].dd_dirname))
            strcat(_DIRS[i].dd_dirname, "\\");
      strcat(strupr(_DIRS[i].dd_dirname), "*.*");
      if (NULL == rfind_1st(_DIRS[i].dd_dirname, FA_ANY, &_DIRS[i].dd_buf))
      {
            DFerr = ENOENT;
            return NULL;
      }
      memcpy(&dstruct, &_DIRS[i].dd_buf, sizeof(struct DSTRUCT));
      do
      {
            ++n;
      } while (rfind_nxt(&_DIRS[i].dd_buf));
      memcpy(&_DIRS[i].dd_buf, &dstruct, sizeof(struct DSTRUCT));
      _DIRS[i].dd_size = n;
      _DIRS[i].dd_loc  = 0;
      _DIRS[i].dd_fd   = i + 1;
      DFerr = SUCCESS;
      return &_DIRS[i];
}

/****************************************************************/
/*                                                              */
/*  closedir()                                                  */
/*                                                              */
/*  Function: Close a preeviously opened directory.             */
/*                                                              */
/*  Parameters: 1 - DOS_DIR pointer of directory to close.      */
/*                                                              */
/*  Returns: SUCCESS or ERROR.                                  */
/*                                                              */
/****************************************************************/

int closedir(DOS_DIR *dirp)
{
      if (0 == dirp->dd_fd || _NDIRS < dirp->dd_fd)
      {
            DFerr = EBADF;
            return ERROR;
      }
      memset(dirp, 0, sizeof(DOS_DIR));
      return SUCCESS;
}

/****************************************************************/
/*                                                              */
/*  rewinddir()                                                 */
/*                                                              */
/*  Function: Reset an open DOS_DIR to its first entry.         */
/*                                                              */
/*  Parameters: 1 - DOS_DIR pointer of directory to rewind.     */
/*                                                              */
/*  Returns: SUCCESS or ERROR.                                  */
/*                                                              */
/****************************************************************/

int rewinddir(DOS_DIR *dirp)
{
      if (0 == dirp->dd_fd || _NDIRS < dirp->dd_fd)
      {
            DFerr = EBADF;
            return ERROR;
      }
      rfind_1st(dirp->dd_dirname, FA_ANY, &(dirp->dd_buf));
      dirp->dd_loc = 0;
      return SUCCESS;
}

/****************************************************************/
/*                                                              */
/*  seekdir()                                                   */
/*                                                              */
/*  Function: Point to a selected entry in a DOS_DIR.           */
/*                                                              */
/*  Parameters: 1 - DOS_DIR pointer of directory to rewind.     */
/*              2 - Offset of entry to seek                     */
/*              3 - Origin of offset                            */
/*                                                              */
/*  Returns: A DSTRUCT pointer, same as returned by rfind_1st() */
/*           and rfind_nxt().                                   */
/*                                                              */
/*           NULL if error, DFerr set as follows:               */
/*           SUCCESS - No error                                 */
/*           EBADF   - Bad file (DOS_DIR) pointer               */
/*           EACCES  - Illegal origin specification             */
/*           EOF     - Attempt to seek past end of directory    */
/*                                                              */
/****************************************************************/

struct DSTRUCT *seekdir(DOS_DIR *dirp, int offset, int origin)
{
      int i, loc;

      if (0 == dirp->dd_fd || _NDIRS < dirp->dd_fd)
      {
            DFerr = EBADF;
            return NULL;
      }
      switch (origin)
      {
      case SEEK_SET:
            loc = offset + 1;
            break;
      case SEEK_CUR:
            loc = dirp->dd_loc + offset;
            break;
      case SEEK_END:
            loc = dirp->dd_size + offset;
            break;
      default:
            DFerr = EACCES;
            return NULL;
      }

      if (loc > (int)dirp->dd_size || 0 >= loc)
      {
            DFerr = EOF;
            return NULL;
      }

      rewinddir(dirp);
      for (i = 0; i < loc; ++i)
            readdir(dirp);

      DFerr = SUCCESS;
      return (&(dirp->dd_buf));
}

/****************************************************************/
/*                                                              */
/*  readdir()                                                   */
/*                                                              */
/*  Function: Reads entries from an open directory.             */
/*                                                              */
/*  Parameters: 1 - DOS_DIR pointer of directory to read.       */
/*                                                              */
/*  Returns: A DSTRUCT pointer, same as returned by rfind_1st() */
/*           and rfind_nxt().                                   */
/*                                                              */
/*           NULL if error, DFerr set as follows:               */
/*           SUCCESS - No error                                 */
/*           EBADF   - Bad file (DOS_DIR) pointer               */
/*           EOF     - Attempt to read past end of directory    */
/*                                                              */
/*  Side effects: The dd_loc element of the DOS_DIR structure   */
/*                will contain a number representing which      */
/*                element of the directory was returned. It may */
/*                range from 1 to dd_size.                      */
/*                                                              */
/****************************************************************/

struct DSTRUCT *readdir(DOS_DIR *dirp)
{
      if (0 == dirp->dd_fd || _NDIRS < dirp->dd_fd)
      {
            DFerr = EBADF;
            return NULL;
      }
      if (0 == dirp->dd_loc || NULL != rfind_nxt(&(dirp->dd_buf)))
      {
            dirp->dd_loc += 1;
            DFerr = SUCCESS;
            return (&(dirp->dd_buf));
      }
      else
      {
            DFerr = EOF;
            return NULL;
      }
}
