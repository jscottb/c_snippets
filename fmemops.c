/*
**  FMEMOPS.C - Emulate MSC's far memory functions in BC++ & ZTC++
**
**  Original Copyright 1988-1992 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/

#include <stdlib.h>
#include <string.h>
#include <dos.h>

#if defined(__TURBOC__) || defined(__ZTC__)

#ifdef __TURBOC__
 #define FAR far
#else
 #define FAR _far
#endif

typedef unsigned char FAR *FarBytePtr;

void FAR * _fmemcpy(void FAR *dest, void FAR *src, size_t count)
{
      movedata(FP_SEG(src), FP_OFF(src), FP_SEG(dest), FP_OFF(dest), count);
      return dest;
}

void FAR * _fmemmove(void FAR *dest, void FAR *src, size_t count)
{
      void FAR *target =  dest;
      FarBytePtr to = (FarBytePtr)dest, from = (FarBytePtr)src;

      if (src >= dest)
            _fmemcpy(dest, src, count);
      else  for (to += count, from += count; count; --count)
                  *--to = *--from;
      return target;
}

void FAR * _fmemset(void FAR *dest, int ch, size_t count)
{
      void FAR *target =  dest;
      FarBytePtr to = (FarBytePtr)dest;

      for ( ; count; --count)
            *to++ = (unsigned char) ch;
      return target;
}

#endif
