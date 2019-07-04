/*
** scalar date routines    --    public domain by Ray Gardner
** These will work over the range 1/01/01 thru 14699/12/31
*/

/*
**  Define ISO to be 1 for ISO (Mon-Sun) calendars
**
**  ISO defines the first week with 4 or more days in it to be week #1.
*/

#ifndef ISO
 #define ISO 0
#endif

#if (ISO != 0 && ISO != 1)
 #error ISO must be set to either 0 or 1
#endif

int isleap (unsigned yr);
long ymd_to_scalar (unsigned yr, unsigned mo, unsigned day);
void scalar_to_ymd (long scalar, unsigned *yr, unsigned *mo, unsigned *day);
int dow(unsigned yr, unsigned mo, unsigned day);
int valiDate(unsigned yr, unsigned mo, unsigned day);
int dow(unsigned yr, unsigned mo, unsigned day);
int daynum(int year, int month, int day);
int weeknum(int year, int month, int day);
