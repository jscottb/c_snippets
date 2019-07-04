/*
**  Find out if a FILE * is valid
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>

#ifdef __TURBOC__
 #define STREAM_BUF     _streams
 #define FCNT           FOPEN_MAX
 #define FLAG           flags
#else /* MSC, ZTC++ */
 #define STREAM_BUF     _iob
 #define FCNT           _NFILE
 #define FLAG           _flag
#endif

typedef enum {FALSE, TRUE} LOGICAL;

int isfopen(FILE *fp)
{
      int i;

      for (i = 0; i < FCNT; ++i)
      {
            if (0 != STREAM_BUF[i].FLAG && fp == &STREAM_BUF[i])
                  return TRUE;
      }
      return FALSE;
}

#ifdef TEST

void main(void)
{
      printf("stdout is%s valid\n", isfopen(stdout) ? "":" not");
      printf("buffer #10 is%s valid\n", isfopen(&STREAM_BUF[9]) ? "":" not");
}

#endif /*TEST */
