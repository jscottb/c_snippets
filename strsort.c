/*
**  strsort() -- Shell sort an array of string pointers via strcmp()
**  public domain by Ray Gardner   Denver, CO   12/88
*/

#include <string.h>
#include <stddef.h>

void strsort (char **array, size_t array_size)
{
      size_t gap, i, j;
      char **a, **b, *tmp;

      for (gap = 0; ++gap < array_size; )
            gap *= 2;
      while (gap /= 2)
      {
            for (i = gap; i < array_size; i++)
            {
                  for (j = i - gap; ;j -= gap)
                  {
                        a = array + j;
                        b = a + gap;
                        if (strcmp(*a, *b) <= 0)
                              break;
                        tmp = *a;
                        *a = *b;
                        *b = tmp;
                        if (j < gap)
                              break;
                  }
            }
      }
}
