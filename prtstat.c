/*
**  PRTSTAT.H - Header file for PRTSTAT.C
*/

#ifndef PRTSTAT_H
 #define PRTSTAT_H

struct PrStatus {
      unsigned int timeout  : 1;
      unsigned int unused   : 2;
      unsigned int IOerror  : 1;
      unsigned int selected : 1;
      unsigned int paperout : 1;
      unsigned int ack      : 1;
      unsigned int notbusy  : 1;
};

int prtstat(unsigned int);

#endif

/*** End of PRTSTAT.H *******************************************************/

/*
**  PRTSTAT.C - Determine printer status
**
**  public domain by Bob Stout
*/

#include <dos.h>

#ifndef PRTSTAT_H
 #include "prtstat.h"
#endif

/*
**  prtstat() - Call with printer number (0 = LPT1, 1 = LPT2, 2 = LPT3)
**
**  Returns status which can be mapped to a PrStatus struct
*/

int prtstat(unsigned int printer_no)
{
      union REGS regs;

      regs.h.ah = 2;
      regs.x.dx = printer_no;
      int86(0x17, &regs, &regs);
      return regs.h.ah;
}

#ifdef TEST

#include <stdio.h>

#define show(x) printf(#x" is %strue (LPT1)\n", mystat.x ? "" : "not ");

void main(void)
{
      struct PrStatus mystat;

      *((int *)&mystat) = prtstat(0);
      show(notbusy);
      show(selected);
      show(paperout);
}

#endif
