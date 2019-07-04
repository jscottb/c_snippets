/*
**  DRVALID.C - validate disk drives
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
**
**  Uses ABSDISKC.C and ABSDISK.ASM in SNIPPETS.
*/

#include <dos.h>
#include <stdlib.h>

typedef enum {ERROR = -1, SUCCESS, FALSE = 0, TRUE} LOGICAL;

/*
**  Function to read an absolute disk sector
*/

int AbsDiskRead(unsigned short, size_t, size_t, void *);

/*
**  getdrv()
**
**  Just as getcwd() returns the default directory, getdrv() returns
**  the current drive.
**
**  Arguments: None.
**
**  Returns:   Current drive (0 = A:, 1 = B:, etc.)
**
**  Side effects: none
*/

int getdrv(void)
{
      union REGS regs;

      regs.h.ah = 0x19;
      intdos(&regs, &regs);
      return (regs.h.al);
}

/*
**  chdrv()
**
**  Like chdir(), except changes drives rather than directories.
**
**  Arguments: 1 - target drive (0 = A:, 1 = B:, etc.)
**
**  Returns: SUCCESS or ERROR
**
**  Side effects: none
*/

LOGICAL chdrv(int drive)
{
      union REGS regs;

      regs.h.ah = 0x0e;
      regs.h.dl = (char)drive;
      intdos(&regs, &regs);
      if (drive != getdrv())
            return ERROR;
      else  return SUCCESS;
}

/*
**  drvalid()
**
**  Verifies whether a logical disk drive is available without
**  triggering the DOS critical error handler.
**
**  Arguments: 1 - target drive (0 = A;, 1 = B:, etc.)
**
**  Returns:   TRUE  - drive is valid
**             FALSE - drive is invalid
**
**  Side effects: none
*/

LOGICAL drvalid(int drive)
{
      int original, result;

      original = getdrv();
      result   = (SUCCESS == chdrv(drive));
      chdrv(original);
      return result;
}

/*
**  drvrdy()
**
**  Checks whether a drive with removable media is ready.
**
**  Arguments: 1 - target drive (0 = A;, 1 = B:, etc.)
**
**  Returns:   TRUE  - drive is ready
**             FALSE - drive is not ready
**             ERROR - other read error
**
**  Side effects: none
*/

LOGICAL drvrdy(int drive)
{
      int status;
      char buf[2048];         /* nice & roomy   */

      status = AbsDiskRead(drive, 1, 0, buf);
      if (0 == status)
            return TRUE;
      status &= 0xff;
      if (2 == status)
            return FALSE;
      else  return ERROR;
}

#ifdef TEST

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
      int drive;

      if (2 > argc)
      {
            puts("Usage: DRVALID drive[:]");
            return EXIT_FAILURE;
      }
      drive = toupper(*argv[1]);
      if (!isalpha(drive))
      {
            puts("Error: Invalid drive name");
            return EXIT_FAILURE;
      }
      printf("Drive %c: is %svalid\n", drive,
            drvalid(drive - 'A') ? "" : "not ");
      if (2 < _osmajor)
      {
            union REGS regs;

            regs.x.ax = 0x4408;
            regs.h.bl = (unsigned char)(drive - '@');
            intdos(&regs, &regs);
            printf("ioctl returned Cflag=%s\n",
                  regs.x.cflag ? "TRUE" : "FALSE");
            printf("ioctl returned AX=0x%X\n", regs.x.ax);
            printf("Drive %c is%s removable\n", drive,
                  regs.x.ax ? " not" : "");
            if (0 == regs.x.ax)
            {
                  printf("Drive %c is %sready\n", drive,
                        drvrdy(drive - 'A') ? "" : "not ");
            }
      }
      return EXIT_SUCCESS;
}

#endif /* TEST */
