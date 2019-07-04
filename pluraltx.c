/*
**  PLURALTX.C - How to print proper plurals
**
**  public domain - original algorithm by Bob Stout
*/

#include <stdio.h>

#define plural_text(n) &"s"[(1 == (n))]
#define plural_text2(n) &"es"[(1 == (n)) << 1]

void main(void)
{
      int i;

      for (i = 0; i < 10; ++i)
            printf("%d thing%s in %d box%s\n", i, plural_text(i),
                  i, plural_text2(i));
}
