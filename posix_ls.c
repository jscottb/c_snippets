/*
**  POSIX_LS.C - Directory lister using POSIX style processing
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <stdio.h>
#include "dirent.h"

#define SUCCESS 0

void dumpdir(char *dirname, char *mask)
{
      DOS_DIR *dirp;
      struct DSTRUCT *dstruct;

      dirp = opendir(dirname);
      if (!dirp)
      {
            printf("Opening %s returned NULL\n\n", dirname);
            return;
      }
      printf("Dir %s has %d entries\n", dirname, dirp->dd_size);
      do
      {
            if (NULL != (dstruct = readdir(dirp)))
            {
                  if (SUCCESS == dirmask(dstruct, mask, NULL, FA_ANY, 0))
                        printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
            }
            else  puts("EOF\n");
      } while (dstruct);
      printf("seekdir( -1) returned %p\n", seekdir(dirp, -1, SEEK_SET));
      printf("seekdir(999) returned %p\n", seekdir(dirp, 999, SEEK_SET));
      printf("seekdir(0, SEEK_SET) returned %p\n", dstruct = seekdir(dirp,
            0, SEEK_SET));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(1, SEEK_SET) returned %p\n", dstruct = seekdir(dirp,
            1, SEEK_SET));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(4, SEEK_SET) returned %p\n", dstruct = seekdir(dirp,
            4, SEEK_SET));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(4, SEEK_CUR) returned %p\n", dstruct = seekdir(dirp,
            4, SEEK_CUR));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(-1, SEEK_CUR) returned %p\n", dstruct = seekdir(dirp,
            -1, SEEK_CUR));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(1, SEEK_CUR) returned %p\n", dstruct = seekdir(dirp,
            1, SEEK_CUR));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(0, SEEK_END) returned %p\n", dstruct = seekdir(dirp,
            0, SEEK_END));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(-1, SEEK_END) returned %p\n", dstruct = seekdir(dirp,
            -1, SEEK_END));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      printf("seekdir(-4, SEEK_END) returned %p\n", dstruct = seekdir(dirp,
            -4, SEEK_END));
      printf("%3d - %s\n", dirp->dd_loc, dstruct->NAME);
      closedir(dirp);
}

void main(int argc, char *argv[])
{
      int i;
      char *mask = NULL, *dirname;

      if (1 < argc)
            dirname = argv[1];
      else  dirname = ".";

      if (2 < argc)
            mask = argv[2];
      printf("Calling dumpdir(%s, %s)\n\n", dirname, mask);
      dumpdir(dirname, mask);
}
