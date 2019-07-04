/*
**  CAL - a calendar for DOS
**
**  a public domain demo using Ray Gardner's SCALDATE.C scalar date functions
**  by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>

/*
**  function prototypes for SCALDATE.C
*/

int isleap (unsigned);
long ymd_to_scalar (unsigned, unsigned, unsigned);

/*
**  calendar generation information
*/

int days[12]    = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char *daynames[8] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

/*
**  box drawing stuff
*/

#ifdef MSDOS
 const char *topborder = "\xd5\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"
                         "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"
                         "\xcd\xcd\xcd\xcd\xb8";
 const char *midborder = "\xc6\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"
                         "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"
                         "\xcd\xcd\xcd\xcd\xb5";
 const char *botborder = "\xd4\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"
                         "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"
                         "\xcd\xcd\xcd\xcd\xbe";
 const char *line = "\xb3";
#else
 const char *line = "";
#endif

/*
**  tell 'em they messed up
*/

void usage(void)
{
      puts("Usage: CAL m y");
      puts("where: m = month (1 - 12)");
      puts("       y = year (1 - 99, 1800 - 3000)");
      exit(-1);
}

/*
**  Define ISO to be 1 for ISO (Mon-Sun) calendars
*/

#ifndef ISO
 #define ISO 0
#endif

#if (ISO != 0 && ISO != 1)
 #error ISO must be set to either 0 or 1
#endif

/*
**  here's where the real work's done
*/

int main(int argc, char *argv[])
{
      int day, day_1, numdays, i, j;
      unsigned yr, mo;

      if (3 > argc)
            usage();

      yr = atoi(argv[2]);
      mo = atoi(argv[1]);

      if (!mo || 12 < mo)
            usage();

      if (100 > yr)
            yr += 1900;

      if (3000 < yr || 1800 > yr)
            usage();

      for (i = 0, mo -= 1; i < 3; ++i, ++mo)
      {
            if (!mo)
            {
                  mo = 12;
                  --yr;
            }
            if (12 < mo)
            {
                  mo = 1;
                  ++yr;
            }
            numdays = days[mo - 1];
            if (2 == mo && isleap(yr))
                  ++numdays;
            day_1 = (int)((ymd_to_scalar(yr, mo, 1) - (long)ISO) % 7L);

#ifdef MSDOS
            if (!i)
                  puts(topborder);
#endif
            fputs(line, stdout);
            for (j = 0; j < 7; )
            {
                  fputs(daynames[ISO + j], stdout);
                  if (7 != ++j)
                        fputc(' ', stdout);
            }
            printf("%s < %s, %d\n%s", line, month[mo - 1], yr, line);

            for (day = 0; day < day_1; ++day)
                  fputs("    ", stdout);
            for (day = 1; day <= numdays; ++day, ++day_1, day_1 %= 7)
            {
                  if (!day_1 && 1 != day)
                        printf("\b%s\n%s", line, line);
                  printf("%3d ", day);
            }
            for ( ; day_1; ++day_1, day_1 %= 7)
                  fputs("    ", stdout);
#ifdef MSDOS
            printf("\b%s\n", line);
            if (2 > i)
                  puts(midborder);
            else  puts(botborder);
#else
            fputc('\n', stdout);
#endif
      }
      return 0;
}
