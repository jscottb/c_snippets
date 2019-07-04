/*
** is_share() - This is a routine that allows a program to determine
**              if file-sharing is enabled at run-time.
**
**              What does this code do?  First - it checks to make sure
**              it is running under DOS 3.0+ - otherwise - no sharing.
**              Next, it opens the program itself (the .EXE file) by using
**              "argv[0]".  This argument points to the actual program name
**              complete with the path under DOS 3.0 or later.  It then
**              attempts to lock the first 500 bytes of the program on
**              disk.  If successful (i.e. return != -1), it unlocks the
**              locked bytes and closes the file (actually the unlock is
**              superfluous since closing the file releases all locks) and
**              returns the a "TRUE" (1) result.  If it fails, it closes
**              the .EXE file and returns a "FALSE" (0) result.  Note that
**              this does not depend on opening a file in shared mode to
**              test it.
**
** Example of usage:
**
** main(int argc, char *argv[])
** {
**   int sharing;
**
**   sharing = is_share(argv[0]);
**   .
**   .
**   if (sharing)
**   {
**     // open file in shared mode
**     ...
**   }
**   else
**   {
**     // use "normal" open
**     ...
**   }
** }
**
** Revision History:
**
** 08/03/93  Original:  "is_sharing()" by Mike Ratledge of fidonet
** 10/20/93  Revision:  revised for library
** 04/03/94  Revision:  "Portabalized" for SNIPPETS by Bob Stout
*/

#include <stdio.h>
#include <io.h>
#include <dos.h>

#if defined(_MSC_VER)
 #include <stdlib.h>
 #include <sys\locking.h>

 int lock(int fp, long ofs, long lng)
 {
       lseek(fp,0L,SEEK_SET);
       return locking(fp,LK_LOCK,lng);
 }

 int unlock(fp,ofs,lng)
 {
       lseek(fp,0L,SEEK_SET);
       return locking(fp,LK_UNLCK,lng);
 }
#endif

int is_share(char *arg)
{
      FILE *exe;

      if (_osmajor < 3)
            return(0);

      exe = fopen(arg, "rb");

      if (0 == lock(fileno(exe), 0l, 500l))
      {
            unlock(fileno(exe), 0l, 500l);
            fclose(exe);
            return(1);
      }

      fclose(exe);
      return(0);
}
