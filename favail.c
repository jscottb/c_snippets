/*
**  Find out how many more files can be fopen'ed
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

int favail(void)
{
      int i, count;

      for (i = count = 0; i < FCNT; ++i)
      {
            if (0 == STREAM_BUF[i].FLAG)
                  ++count;
      }
      return count;
}

#ifdef TEST

void main(void)
{
      char *fname = "A$$$$$$$.$$$";
      FILE *fp;

      do
      {
            int i = favail();

            printf("You can fopen %d new file%s\n", i, &"s"[i == 1]);
            fp = fopen(fname, "w");
            *fname += 1;
      } while (fp);

      do
      {
            printf("removing %s\n", fname);
            remove(fname);
      } while ('A' <= --(*fname)) ;
}

#endif /*TEST */
