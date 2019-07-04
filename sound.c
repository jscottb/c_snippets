/*
**  SOUND.C
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include "sound.h"

void soundon(void)
{
      short value;

      value = inp(SCNTRL);
      value |= SOUNDON;
      outp(SCNTRL, value);
}

void soundoff(void)
{
      short value;

      value = inp(SCNTRL);
      value &= SOUNDOFF;
      outp(SCNTRL, value);
}
