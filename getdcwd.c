/*
** GETDCWD.C - returns the current working directory for a specific drive
**
** public domain by Bob Jarvis, modified by Bob Stout
*/

#if defined(__ZTC__)
 #define GetDrive(d) dos_getdrive(&d)
 #define FAR _far
#elif defined(__TURBOC__)
 #define GetDrive(d) ((d) = getdisk() + 1)
 #define FAR far
#else /* assume MSC */
 #define GetDrive(d) _dos_getdrive(&d)
 #define FAR _far
#endif

#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char *getdcwd(unsigned int drive)   /* 0 = current, 1 = A, 2 = B, etc */
{
      union REGS regs;
      struct SREGS sregs;
      char *retptr;

      retptr = calloc(FILENAME_MAX + 4, sizeof(char));
      if(retptr == NULL)
            return NULL;

      if(drive == 0)    /* figure out which drive is current */
      {
            GetDrive(drive);
            drive += 1;
      }

      *retptr = (char)((drive-1) + 'A');
      *(retptr+1) = ':';
      *(retptr+2) = '\\';

      segread(&sregs);
      regs.h.ah = 0x47;
      regs.h.dl = (unsigned char)drive;
      sregs.ds  = FP_SEG((void FAR *)retptr);
      regs.x.si = FP_OFF((void FAR *)retptr) + 3;

      intdosx(&regs, &regs, &sregs);
      if (15 == regs.x.ax)     /* drive number invalid */
      {
            free(retptr);
            return NULL;
      }
      else  return retptr;
}

#ifdef TEST

void main(int argc, char *argv[])
{
      char *curpath;
      unsigned int n;

      if(argc > 1)
            n = (tolower(*argv[1]) - 'a') + 1;
      else  GetDrive(n);
      
      printf("curpath = '%s'\n", curpath = getdcwd(n));
      if (curpath)
            free(curpath);
}

#endif
