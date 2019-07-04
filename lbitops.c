/*
**  large bit array operations by Scott Dudley
**  with modifications by Auke Reitsma and Bob Stout
**
**  Public domain
*/

#include <limits.h>

/*
**  The following macros assume CHAR_BIT is one of either 8, 16, or 32
*/

#define MASK  CHAR_BIT-1
#define SHIFT ((CHAR_BIT==8)?3:(CHAR_BIT==16)?4:8)

#define BitOff(a,x)  ((void)((a)[(x)>>SHIFT] &= ~(1 << ((x)&MASK))))
#define BitOn(a,x)   ((void)((a)[(x)>>SHIFT] |=  (1 << ((x)&MASK))))
#define BitFlip(a,x) ((void)((a)[(x)>>SHIFT] ^=  (1 << ((x)&MASK))))
#define IsBit(a,x)   ((a)[(x)>>SHIFT]        &   (1 << ((x)&MASK)))

#include <stdio.h>
#include <string.h>

int main(void)
{
      char array[64];

      memset(array, '\0', sizeof(array));

      BitOn(array, 5);
      BitOn(array, 12);
      BitOn(array, 500);

      if (IsBit(array, 5) && IsBit(array, 12) && IsBit(array, 500))
            puts("These functions seem to work!");
      else  puts("Something's broken here!");

      BitFlip(array, 12);
      BitOff(array, 5);

      if (!IsBit(array, 5) && !IsBit(array, 12) && IsBit(array, 500))
            puts("These functions still seem to work!");
      else  puts("Something's broken here!");
      return 0;
}
