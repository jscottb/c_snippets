/*
**  SETIMETO.C - Set the timestamp of one file to match another.
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>

#ifdef __ZTC__
 #define GETFTIME dos_getftime
 #define SETFTIME dos_setftime
#else
 #define GETFTIME _dos_getftime
 #define SETFTIME _dos_setftime
#endif

int main(int argc, char *argv[])
{
      int fd0, fd1;

#ifdef __TURBOC__
      struct ftime Ftime;
#else
      unsigned date, time;
#endif

      if (3 > argc)
      {
            puts("Usage: SETIMETO old_filename new_filename");
            return EXIT_FAILURE;
      }

      if (-1 == (fd0 = open(argv[1], O_RDONLY)))
      {
            printf("Unable to open %s\n", argv[1]);
            return EXIT_FAILURE;
      }

#ifdef __TURBOC__                         /* Save the time/date         */
      getftime(fd0, &Ftime);
#else
      GETFTIME(fd0, &date, &time);
#endif

      if (-1 == (fd1 = open(argv[2], O_WRONLY)))
      {
            printf("Unable to open %s\n", argv[2]);
            return EXIT_FAILURE;
      }

#ifdef __TURBOC__                         /* Set the time/date          */
      setftime(fd1, &Ftime);
#else
      SETFTIME(fd1, date, time);
#endif

      close(fd0);
      close(fd1);
      return EXIT_SUCCESS;
}
