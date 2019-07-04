/* code to disable <Ctrl><Alt><Del>.                                */
/* Compiled and tested under TC++ and MSC 6                         */

#include <dos.h>
#include <conio.h>

#if defined(__TURBOC__)
 #define _interrupt interrupt
 #define _far far
#else                              /* i.e. if MSC                   */
 #define inportb(port) inp(port)
 #define outportb(port,val) outp(port,val)
 #define enable() _enable()
 #define disable() _disable()
 #define getvect(int) _dos_getvect(int)
 #define setvect(int,ptr) _dos_setvect(int,ptr)
 unsigned char peekb(unsigned seg, unsigned ofs)
 {
         unsigned char far *ptr;

         FP_SEG(ptr) = seg;
         FP_OFF(ptr) = ofs;
         return *ptr;
 }
#endif

#define CTRLALT        (0x08|0x04) /* bit flags set in kbstat()     */
#define DELSCAN        0x53        /* keyboard scan code for <Del>  */
#define KEYPORT        0x60        /* keyboard scan code port       */
#define CONTROLLERPORT 0x20        /* interrupt controller port     */
#define kbstat()       peekb(0,0x417)  /* BIOS data area - kb flags */

#define keyport()      inportb(KEYPORT)
        /* macro that returns the scancode of the key that caused   */
        /* the interrupt                                            */

#define install()      (oldkbisr=getvect(0x09),setvect(0x09,newkbisr))
        /* installation macro, installs newkbisr() in the keyboard  */
        /* interrupt chain                                          */

#define uninstall()       setvect(0x09,oldkbisr)
        /* removal macro, call to remove newkbisr() from interrupt  */
        /* chain.  oldkbisr()  must be removed before program ends  */

void (_interrupt _far * oldkbisr)(void);
        /* address of old keyboard ISR                              */

void _interrupt _far newkbisr(void)
{
   if((keyport()==DELSCAN)&&((kbstat()&CTRLALT)==CTRLALT))
   {
       char kbin = (char)inportb(KEYPORT+1);      /* reset keyboard */

       outportb(KEYPORT+1, kbin|0x80);
       outportb(KEYPORT+1, kbin);
       disable();
       outportb(CONTROLLERPORT,0x20); /* tell controller to shut up */
       enable();
   }
   else
       oldkbisr();  /* chain to old keyboard isr */
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <signal.h>
#include <errno.h>

void main(void)
{
      int ch = 0;
      void cleanup(void), cbrk(int);

      install();
      atexit(cleanup);

      signal(SIGINT, cbrk);

      puts("This is a test of Ctrl-Alt-Del disabling.");
      puts("Press any key, but only Esc should stop this program.");

      while (0x1b != ch)
      {
            if (kbhit)
                  ch = getch();
      }
}

void cbrk(int sig)
{
      signal(SIGINT, SIG_IGN);
      signal(SIGINT, cbrk);
}

void cleanup(void)
{
      uninstall();
}

#endif
