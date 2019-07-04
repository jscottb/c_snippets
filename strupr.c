/*
**  Portable, public domain strupr() & strlwr()
*/

#include <ctype.h>

char *strupr(char *str)
{
      char *string = str;

      if (str)
      {
            for ( ; *str; ++str)
                  *str = toupper(*str);
      }
      return string;
}

char *strlwr(char *str)
{
      char *string = str;

      if (str)
      {
            for ( ; *str; ++str)
                  *str = tolower(*str);
      }
      return string;
}
