/*
** DosDate macros - access bitfield values from DOS file date & time
**  for Borland C and C++ compilers by: Wayne Hamilton
*/

#define dd_yr(d)      (((struct { unsigned day:5, mo:4, yr:7; } *) &d)->yr)
#define dd_mo(d)      (((struct { unsigned day:5, mo:4, yr:7; } *) &d)->mo)
#define dd_day(d)     (((struct { unsigned day:5, mo:4, yr:7; } *) &d)->day)
#define dd_hr(t)      (((struct { unsigned sec:5, mn:6, hr:5; } *) &t)->hr)
#define dd_mn(t)      (((struct { unsigned sec:5, mn:6, hr:5; } *) &t)->mn)
#define dd_sec(t)     (((struct { unsigned sec:5, mn:6, hr:5; } *) &t)->sec)

/* then: year = dd_yr(ffblk.ff_date); */

#ifdef TEST

#include <stdio.h>
#include <dir.h>

main(int argc, char *argv[])
{
      struct ffblk ff;

      findfirst(argv[0], &ff, 0xff);
      printf("%s was saved on %d-%d-%d at %d:%02d:%02d\n", argv[0],
            dd_mo(ff.ff_fdate), dd_day(ff.ff_fdate), dd_yr(ff.ff_fdate),
            dd_hr(ff.ff_ftime), dd_mn(ff.ff_ftime), 2 * dd_sec(ff.ff_ftime));
      return 0;
}

#endif
