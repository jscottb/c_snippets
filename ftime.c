/*
**  Public domain by Jeff Dunlop & Bob Stout
*/

#ifndef __TURBOC__

#include <dos.h>
#include "ftime.h"

#ifdef __ZTC__
 #pragma ZTC align 1
 #define DOS_GETFTIME dos_getftime
 #define DOS_SETFTIME dos_setftime
#else
 #pragma pack(1)
 #define DOS_GETFTIME _dos_getftime
 #define DOS_SETFTIME _dos_setftime
#endif

int _cdecl getftime (int handle, struct ftime *ftimep)
{
      int retval = 0;
      union
      {
            struct
            {
                  unsigned time;
                  unsigned date;
            } msc_time;
            struct ftime bc_time;
      } FTIME;

      if (0 == (retval = DOS_GETFTIME(handle, &FTIME.msc_time.date,
            &FTIME.msc_time.time)))
      {
            *ftimep = FTIME.bc_time;
      }
      return retval;
}

int _cdecl setftime (int handle, struct ftime *ftimep)
{
      union
      {
            struct
            {
                  unsigned time;
                  unsigned date;
            } msc_time;
            struct ftime bc_time;
      } FTIME;

      FTIME.bc_time = *ftimep;

      return DOS_SETFTIME(handle, FTIME.msc_time.date, FTIME.msc_time.time);
}

#endif /* __TURBOC__ */
