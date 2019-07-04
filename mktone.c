/*
**  MKTONE.C
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include "uclock.h"
#include "sound.h"

static int usec_timeout(uclock_t start, uclock_t finish, uclock_t usecs)
{
      if (usecs >= (finish - start))
            return 0;
      else  return 1;
}

void dosound(int freq)
{
      unsigned i;

      outp(C8253, SETIMER);
      i = (unsigned)freq%256;
      outp(F8253, i);
      i = (unsigned)freq/256;
      outp(F8253, i);
}

void mktone(int freq, int update, unsigned delay)
{
      uclock_t start;

      if (0 == freq)
      {
            soundoff();
            return;
      }
      dosound(freq);
      if (update != UPDATE)
            soundon();
      if (delay == 0)
            return;
      start = usec_clock();
      while (!usec_timeout(start, usec_clock(), 1000L * (long)delay))
            ;
      if (update == TOGGLE)
            soundoff();
}
