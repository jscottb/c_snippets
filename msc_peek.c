/*
**  For MSC which lacks these very basic (sic) functions
**
**  public domain by Bob Stout
*/

#include <dos.h>

#ifndef MK_FP
 #define MK_FP(seg,offset) \
        ((void _far *)(((unsigned long)(seg)<<16) | (unsigned)(offset)))
#endif

unsigned char peekb(unsigned seg, unsigned ofs)
{
        unsigned char _far *ptr;

        FP_SEG(ptr) = seg;
        FP_OFF(ptr) = ofs;
        return *ptr;
}

unsigned peek(unsigned seg, unsigned ofs)
{
        unsigned _far *ptr;

        FP_SEG(ptr) = seg;
        FP_OFF(ptr) = ofs;
        return *ptr;
}

void pokeb(unsigned seg, unsigned ofs, unsigned char ch)
{
        unsigned char _far *ptr;

        FP_SEG(ptr) = seg;
        FP_OFF(ptr) = ofs;
        *ptr = ch;
}

void poke(unsigned seg, unsigned ofs, unsigned num)
{
        unsigned _far *ptr;

        FP_SEG(ptr) = seg;
        FP_OFF(ptr) = ofs;
        *ptr = num;
}
