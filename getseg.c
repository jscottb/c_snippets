/*
**  GETSEG.C - How to get the memory segment of an object
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <dos.h>

#ifdef __TURBOC__
 #define FAR far
#else
 #define FAR _far
#endif

#define GetSeg(obj) (unsigned)((unsigned long)(((void FAR *)(obj))) >> 16)
#define GetOfs(obj) (unsigned)((unsigned long)(((void FAR *)(obj))) & 0xffff)

int dummyv = 0;

int dummyf(void)
{
      return dummyv;
}

void main(void)
{
      struct SREGS sregs;

      segread (&sregs);
      printf("DS = %04X, CS = %04X\n", sregs.ds, sregs.cs);

#if defined(__ZTC__)
      printf("&dummyv = %lp, dummyf = %lp\n\n",
#else
      printf("&dummyv = %Fp, dummyf = %Fp\n\n",
#endif

#if defined(__ZTC__) || defined(__TURBOC__)
            (int FAR *)&dummyv, (int (FAR *)())dummyf);
#else       /* MSC doesn't allow casting near function pointers to far  */
            (int FAR *)&dummyv, dummyf);
#endif

      printf("GetSeg(dummyv) = %04X, GetSeg(dummyf) = %04X\n",
            GetSeg(&dummyv), GetSeg(dummyf));
      printf("GetOfs(dummyv) = %04X, GetOfs(dummyf) = %04X\n",
            GetOfs(&dummyv), GetOfs(dummyf));
}
