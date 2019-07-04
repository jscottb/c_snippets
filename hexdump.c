/*
**  HEXDUMP.C - Dump a file.
**
**  This Program Written By Paul Edwards w/ modifications by Bob Stout
**  Released to the public domain
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void dodump(FILE *fp, long start, long count);
static void skipb(FILE *fp, long start);

main(int argc, char **argv)
{
      FILE *fp;
      long start, count;

      if (argc < 2)
      {
            puts("Usage: HEXDUMP file_name [start] [length]");
            return (EXIT_FAILURE);
      }
      if (argc > 2)
            start = atol(*(argv + 2));
      else  start = 0L;
      if (argc > 3)
            count = atol(*(argv + 3));
      else  count = -1L;
      fp = fopen(*(argv + 1), "rb");
      if (fp == NULL)
      {
            printf("unable to open file %s for input\n", *(argv+1));
            return (EXIT_FAILURE);
      }
      skipb(fp, start);
      dodump(fp, start, count);
      return (EXIT_SUCCESS);
}

static void dodump(FILE *fp, long start, long count)
{
      int c, pos1, pos2;
      long x = 0L;
      char prtln[100];

      while (((c = fgetc(fp)) != EOF) && (x != count))
      {
            if (x%16 == 0)
            {
                  memset(prtln,' ',sizeof prtln);
                  sprintf(prtln,"%0.6X   ", start + x);
                  pos1 = 8;
                  pos2 = 45;
            }
            sprintf(prtln + pos1, "%0.2X", c);
            if (isprint(c))
                  sprintf(prtln + pos2, "%c", c);
            else  sprintf(prtln + pos2, ".");
            pos1 += 2;
            *(prtln+pos1) = ' ';
            pos2++;
            if (x % 4 == 3)
                  *(prtln + pos1++) = ' ';
            if (x % 16 == 15)
                  printf("%s\n", prtln);
            x++;
      }
      if (x % 16 != 15)
            printf("%s\n", prtln);
      return;
}

static void skipb(FILE *fp, long start)
{
      long x = 0;

      if (start == 0)
            return;
      while (x < start)
      {
            fgetc(fp);
            x++;
      }
      return;
}
