/*
**  ASSIGNPR.C
**
**  Multiple printer support with default to a single printer
**  connected to the PRN device.
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <stdio.h>

#define NUM_OF_PRNTRS 6

FILE *printer[NUM_OF_PRNTRS] = {stdprn};

/*
**  assign_printer()
**
**  Call with printer number and device name
**
**     printer number should be in the range of 0 to NUM_OF_PRNTRS-1
**     device should be "LPT1", "LPT2", "LPT3", "COM1", COM2", or a log file
**
**  Returns 0 if successful, -1 if error
**
**  Then do all printer output with fprintf(), fputs(), fputc(), etc.
**  using printer[printer_number] as the output stream
*/

int cdecl assign_printer(int number, char *device)
{
      FILE *fp;

      if (NUM_OF_PRNTRS <= number || NULL == (fp = fopen(device, "w")))
            return -1;
      printer[number] = fp;
      return 0;
}

#ifdef TEST                                     /* Test code follows    */

main()
{                                       /* Leave printer[0] = stdprn    */
      assign_printer(1, "CON");         /* Set printer[1] to the screen */
      assign_printer(2, "p.log");       /* Set printer[2] to log file   */
      fputs("This is a printer test\n", printer[0]);
      fputs("This is a screen test\n", printer[1]);
      fputs("This is a log test\n", printer[2]);
}

#endif /* TEST */
