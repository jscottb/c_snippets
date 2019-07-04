/*
**  FCOMPARE.C - Compare 2 files
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {ERROR = -1, SUCCESS, FAIL};

#define BUFSIZE 16384
static char buf[2][BUFSIZE];

int fcompare(const char *fname1, const char *fname2)
{
      FILE *f1, *f2;
      int retval = SUCCESS;

      if (NULL == (f1 = fopen(fname1, "rb")))
            return ERROR;
      if (NULL != (f2 = fopen(fname2, "rb")))
      {
            size_t size1, size2;

            do
            {
                  size1 = fread(buf[0], 1, BUFSIZE, f1);
                  size2 = fread(buf[1], 1, BUFSIZE, f2);
                  if (0 == (size1 | size2))
                        break;
                  if ((size1 != size2) || memcmp(buf[0], buf[1], size1))
                  {
                        retval = FAIL;
                        break;
                  }
            } while (size1 && size2);
            fclose(f2);
      }
      else  retval = ERROR;
      fclose(f1);
      return retval;
}

#ifdef TEST

int main(int argc, char *argv[])
{
      if (3 > argc)
      {
            puts("Usage: FCOMPARE file1 file2");
            return 1;
      }
      printf("fcompare(%s, %s) returned %d\n", argv[1], argv[2],
            fcompare(argv[1], argv[2]));
}

#endif /* TEST */
