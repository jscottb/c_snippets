/*
**  by David Goodenough & Bob Stout
*/

#ifdef __TURBOC__
 #define FAR far
#else
 #define FAR _far
#endif

#ifndef MK_FP
 #define MK_FP(seg,offset) \
        ((void FAR *)(((unsigned long)(seg)<<16) | (unsigned)(offset)))
#endif
 
#define biosseg 0x40

int fast_kbhit(void)
{
      return *((unsigned FAR *)MK_FP(biosseg, 0x1a)) -
            *((unsigned FAR *)MK_FP(biosseg, 0x1c));
}

void fast_kbflush(void)
{
      *((unsigned FAR *)MK_FP(biosseg, 0x1a)) =
            *((unsigned FAR *)MK_FP(biosseg, 0x1c));
}
