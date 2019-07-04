/****************************************************************/
/* Name: noctrl()                                               */
/* Desc: captures interrput 9 so as to ignore ctrl-c,ctrl-break,*/
/*       ctrl-alt-del                                           */
/****************************************************************/

#include <dos.h>

#if defined(__ZTC__)
 #define INTERRUPT
 #define FAR            _far
 #define ENABLE         int_on
 #define INPORTB        inp
 #define OUTPORTB       outp
#else
 #include <conio.h>
 #if defined(__TURBOC__)
  #define INTERRUPT      interrupt
  #define FAR            far
  #define ENABLE         enable
  #define INPORTB        inportb
  #define OUTPORTB       outportb
 #else
  #define INTERRUPT      _interrupt
  #define FAR            _far
  #define ENABLE         _enable
  #define INPORTB        inp
  #define OUTPORTB       outp
 #endif
#endif

extern void (INTERRUPT FAR *oldint9)(void);     /* Caller must set this */

void INTERRUPT FAR noctrl(void)
{
      unsigned char byte;
      static int flag;
 
      ENABLE();
 
      if ((byte = (unsigned char)INPORTB(0x60)) == 29)
            flag = 1;
 
      if (byte == 157)
            flag = 0;
 
      if (!flag)
            (*oldint9)();
      else  switch (byte)
      {
      case 46 :   /* yeah, these should be #defined! */
      case 70 :
      case 56 :
      case 83 :
            byte = (unsigned char)INPORTB(0x61);
            OUTPORTB(0x61,byte | 0x80);
            OUTPORTB(0x61,byte);
            OUTPORTB(0x20,0x20);
            break;
      default :
            (*oldint9)();
      }
}
