/* calsupp.c -- public domain by Ray McVay */

/*  This module provides three handy date related functions:
**       dow() - Returns the day of the week for a given date
**       IsLeap() - Returns 1 if a year is a leap year
**       GetToday() - Returns today's date from the operating system
*/

#include <time.h>

/*
** Returns an integer that represents the day of the week for
**  the date passed as parameters.
**
**   day:    day of month
**   mon:    month (1-12)
**   yr:     year
**
**  returns 0-6 where 0 == sunday
*/

int dow(int day, int mon, int yr)
{
      int dow;

      if (mon <= 2)
      {
            mon += 12;
            yr -= 1;
      }
      dow = (day + mon * 2 + ((mon + 1) * 6) / 10 +
            yr + yr / 4 - yr / 100 + yr / 400 + 2);
      dow = dow % 7;
      return ((dow ? dow : 7) - 1);
}


/*
**  Returns 1 if yr is a leap year, 0 if it is not
*/

int IsLeap(int yr)
{
      if (yr % 400 == 0)  return 1;
      if (yr % 100 == 0)  return 0;
      if (yr % 4 == 0)    return 1;
      else                return 0;
}


/*
**  Returns the current day, month and year in the referenced variables
*/

void GetToday(int *day, int *mon, int *yr)
{
      struct tm   today;
      time_t  ctime;

      time(&ctime);
      today = *localtime(&ctime);
      *day = today.tm_mday;
      *mon = today.tm_mon + 1;
      *yr = today.tm_year + 1900;
}
