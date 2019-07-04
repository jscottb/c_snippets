/*
**  HUGEREAD.C - "Universal" PC read and write functions using huge data
**               and far pointers.
**
**  NOTES:
**
**  1. If these functions are called with a prototype in scope, passed
**     parameters will be coerced to the proper data types.
**
**  2. Since these call read() and write(), all normal mode flags which
**     are supported by individual compilers will be honored.
**
**  3. In small data memory models (S, T, and M), an intermediate buffer
**     is allocated and used. In large data models (L and C), the data
**     are read/written directly from/to target memory.
**
**  4. Like many mixed-model functions, this may generate lots of warnings
**     with many compilers. Despite this, it really does generate correct
**     code for all major PC compilers.
**
**  Original Copyright 1992 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/

#include <dos.h>
#include <io.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __TURBOC__
 #define FAR far
#else
 #define FAR _far
#endif

#ifndef min
 #define min(x,y) (((x) <= (y)) ? (x) : (y))
#endif

#ifndef MK_FP
 #define MK_FP(seg,offset) \
        ((void FAR *)(((unsigned long)(seg)<<16) | (unsigned)(offset)))
#endif

/*
**  Get the largest buffer possible.
*/

static size_t gettmp(char **buf)
{
      size_t bufsiz;

      for (bufsiz = 0x4000; bufsiz >= 128; bufsiz >>= 1)
      {
            if (NULL != (*buf = (char *) malloc(bufsiz)))
                  return bufsiz;
      }
      return 0;
}

/*
**  Normalize a far pointer
*/

void FAR *farnormal(void FAR *ptr)
{
      unsigned long base, para;

      base = (unsigned long)(ptr & 0xffff000fL);
      para = (unsigned long)(ptr & 0x0000fff0L);
      para <<= 12;
      return (void FAR *)(base + para);
}

/*
**  Read any size block to anywhere in memory
*/

long hugeread(int fh, char FAR *buf, long size)
{
      long count;
      size_t bufsiz;
      char *tmp;
      long ercode = size;

      if (4 > sizeof(void *))
      {
            if (0 == (bufsiz = gettmp(&tmp)))
                  return -1L;
      }
      else
      {
            tmp = (char *)buf;
            bufsiz = 0x4000;
      }

      while (0 < (count = min(size, (long)bufsiz)))
      {
            int i, numread = read(fh, tmp, (size_t)count);

            if (1 > numread || numread != (int)count)
                  return -1L;
            if (4 > sizeof(void *))
            {
                  for (i = 0; i < count; ++i)
                        buf[i] = tmp[i];
            }
            buf = farnormal(buf + count);
            size -= count;
            if (2 < sizeof(void *))
                  tmp = (char *)buf;
      }
      return ercode;
}

/*
**  Write any size block from anywhere in memory
*/

long hugewrite(int fh, char FAR *buf, long size)
{
      long count;
      size_t bufsiz;
      char *tmp;
      long ercode = size;

      if (4 > sizeof(void *))
      {
            if (0 == (bufsiz = gettmp(&tmp)))
                  return -1L;
      }
      else
      {
            tmp = (char *)buf;
            bufsiz = 0x4000;
      }

      while (0 < (count = min(size, (long)bufsiz)))
      {
            int i, numwrite;

            if (4 > sizeof(void *))
            {
                  for (i = 0; i < count; ++i)
                        tmp[i] = buf[i];
            }
            numwrite = write(fh, tmp, (size_t)count);
            if (1 > numwrite || numwrite != (int)count)
                  return -1L;
            buf = farnormal(buf + count);
            size -= count;
            if (2 < sizeof(void *))
                  tmp = (char *)buf;
      }
      return ercode;
}

/*
**  Read any size block to anywhere in memory
*/

long hugefread(FILE *fp, char FAR *buf, long size)
{
      long count;
      size_t bufsiz;
      char *tmp;
      long ercode = size;

      if (4 > sizeof(void *))
      {
            if (0 == (bufsiz = gettmp(&tmp)))
                  return -1L;
      }
      else
      {
            tmp = (char *)buf;
            bufsiz = 0x4000;
      }

      while (0 < (count = min(size, (long)bufsiz)))
      {
            int i, numread = fread(tmp, 1, (size_t)count, fp);

            if (1 > numread || numread != (int)count)
                  return -1L;
            if (4 > sizeof(void *))
            {
                  for (i = 0; i < count; ++i)
                        buf[i] = tmp[i];
            }
            buf = farnormal(buf + count);
            size -= count;
            if (2 < sizeof(void *))
                  tmp = (char *)buf;
      }
      return ercode;
}

/*
**  Write any size block from anywhere in memory
*/

long hugefwrite(FILE *fp, char FAR *buf, long size)
{
      long count;
      size_t bufsiz;
      char *tmp;
      long ercode = size;

      if (4 > sizeof(void *))
      {
            if (0 == (bufsiz = gettmp(&tmp)))
                  return -1L;
      }
      else
      {
            tmp = (char *)buf;
            bufsiz = 0x4000;
      }

      while (0 < (count = min(size, (long)bufsiz)))
      {
            int i, numwrite;

            if (4 > sizeof(void *))
            {
                  for (i = 0; i < count; ++i)
                        tmp[i] = buf[i];
            }
            numwrite = fwrite(tmp, 1, (size_t)count, fp);
            if (1 > numwrite || numwrite != (int)count)
                  return -1L;
            buf = farnormal(buf + count);
            size -= count;
            if (2 < sizeof(void *))
                  tmp = (char *)buf;
      }
      return ercode;
}
