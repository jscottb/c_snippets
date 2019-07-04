/*
**  Portable, public domain strdup() by Bob Stout
*/

#include <stdlib.h>
#include <string.h>

char *strdup(const char *string)
{
      char *new;

      if (NULL != (new = malloc(strlen(string) + 1)))
            strcpy(new, string);
      return new;
}
