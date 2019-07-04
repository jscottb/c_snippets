/** int drop_time(void)
**
**   Drops current timeslice in OS/2, Win, DPMI 1.0 and (I think) DV
**
**  Returns:  0 if not successful, 1 if dropped
**
**  Based on Ralf Brown's Interrupt list.
**  Donated to Public Domain by Thor Johnson.
**
***********************************************************************/

#include <dos.h>

int drop_time(void)     /* Drops Time-slice, giving to another program */
{
      union REGS regs;

      regs.x.ax = 0x1680;
      int86(0x2f, &regs, &regs);
      return (regs.h.al == 0x80)? 0 : 1;
}
