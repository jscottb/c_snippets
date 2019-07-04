/*
**  DIRMASK.C - Complex pattern matching
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
#include "dirent.h"

int patmat(const char *, const char *);

typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;
#define SUCCESS 0

/****************************************************************/
/*                                                              */
/*  dirmask()                                                   */
/*                                                              */
/*  Tests a directory entry for matching patterns. Tests both   */
/*  file name and attributes. Tests for both inclusion specs    */
/*  and exclusion specs.                                        */
/*                                                              */
/*  Parameters: 1 - Pointer to the directory entry's FIND       */
/*                  structure                                   */
/*              2 - Filename for inclusion matching, i.e. if    */
/*                  this spec matches the filename, we matched. */
/*                  Use NULL to match anything.                 */
/*              3 - Filename for exclusion matching, i.e. if    */
/*                  this spec matches the filename, we failed.  */
/*                  Use NULL to exclude nothing.                */
/*              4 - Attribute for inclusion mask. Use FA_ANY    */
/*                  to match anything).                         */
/*              5 - Attribute for exclusion mask. Use zero to   */
/*                  exclude nothing).                           */
/*                                                              */
/*  Returns: SUCCESS if name and attribute matched, else ERROR. */
/*                                                              */
/*  Side effects: Converts patterns to upper case               */
/*                                                              */
/****************************************************************/

int dirmask(struct DSTRUCT *dstruct,
            char           *fname_inc,
            char           *fname_exc,
            unsigned        attr_inc,
            unsigned        attr_exc)
{
      if (!dstruct)
            return ERROR;
      strupr(fname_inc);
      strupr(fname_exc);
      if (fname_inc)
      {
            if (TRUE != patmat(dstruct->NAME, fname_inc))
                  return ERROR;
      }
      if (fname_exc)
      {
            if (TRUE == patmat(dstruct->NAME, fname_exc))
                  return ERROR;
      }
      if (!((dstruct->ATTRIBUTE | 0x80) & attr_inc))
            return ERROR;
      if (dstruct->ATTRIBUTE & attr_exc)
            return ERROR;
      return SUCCESS;
}
