/*-------------------------[ IsShift ]--------------------------*/
/*           Determine whether a shift key is depressed         */
/*              public domain snippet by Jeff Dunlop            */
/*--------------------------------------------------------------*/
/* local:                                                       */
/*      key_flags = pointer to bios shift key area              */
/* return:                                                      */
/*      1 if either shift key is depressed                      */
/*--------------------------------------------------------------*/

#if !defined(MK_FP)
    #define MK_FP(seg,off) ((void far *)(((long)(seg) << 16)|(unsigned)(off)))
#endif

int IsShift(void)
{
    unsigned char far *keyflags = MK_FP(0x40, 0x17);

    return (*keyflags & 0x03);
}

/* -or?- */

#define IsShift ((*MK_FP(0x40, 0x17)) & 0x03)
