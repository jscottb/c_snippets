/*
**  Originally published as part of the MicroFirm Function Library
**
**  Copyright 1986, S.E. Margison
**  Copyright 1989-92, Robert B.Stout
**
**  Subset version released to the public domain, 1990
*/

#include <conio.h>

int getkey(void)
{
      int i;

      switch (i = (int)getch())
      {
      case 0xe0:
#ifdef MSDOS
            return i;
#endif
      case 0:
            return 256 + (int)getch();
      default:
            return i;
      }
}
