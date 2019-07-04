/*
**  change_prn()
**
**  A function to change the standard printer device for the duration
**  of a program. Valid new device codes are:
**
**      0 - LPT1
**      1 - LPT2
**      2 - LPT3
**      3 - COM1
**      4 - COM2
**      5 - CON
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <stdio.h>

int change_prn(int device)
{
      char *newdev;

      switch (device)
      {
      case 0:
            newdev = "LPT1";
            break;
      case 1:
            newdev = "LPT2";
            break;
      case 2:
            newdev = "LPT3";
            break;
      case 3:
            newdev = "COM1";
            break;
      case 4:
            newdev = "COM2";
            break;
      case 5:
            newdev = "CON";
            break;
      default:
            return -1;
      }
      return (NULL == freopen(newdev, "w", stdprn));
}
