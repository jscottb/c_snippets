/*
**  ext_getch()
**
**  A getch() work-alike for use with extended keyboards.
**
**  Parameters: none
**
**  Returns: Extended key code as follows:
**           0->255     Normal key
**           256->511   Numeric pad key or Function key
**           512->767   Cursor pad key or Numeric pad
**                      "duplicate" key (Enter, /, *, -, +)
**
**  Original Copyright 1992 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/
 
#include <dos.h>
#include <ctype.h>
 
#define LoByte(x) ((unsigned char)((x) & 0xff))
#define HiByte(x) ((unsigned char)((unsigned short)(x) >> 8))
 
int ext_getch(void)
{
      int key;
      union REGS regs;
 
      regs.h.ah = 0x10;
      int86(0x16, &regs, &regs);
      key = regs.x.ax;
 
      switch (LoByte(key))
      {
      case 0:
            key = HiByte(key) + 256;
            break;
 
      case 0xe0:
            key = HiByte(key) + 512;
            break;
  
      default:
            if (0xe0 == HiByte(key))
                  key = LoByte(key) + 512;
            else
            {
                  if (ispunct(LoByte(key)) && HiByte(key) > 0x36)
                        key = LoByte(key) + 512;
                  else  key = LoByte(key);
            }
      }
      return key;
}
