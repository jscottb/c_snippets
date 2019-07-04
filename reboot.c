/*
**  Public domain demo to reboot a PC
*/
 
#ifdef __TURBOC__
 #define FAR far
#else
 #define FAR _far
#endif
 
short FAR *bios_post = (short FAR *)0x00400072;
void (FAR * boot)(void) = (void (FAR *)())0xffff0000;
 
void reboot(warm)
{
      if (warm)
            *bios_post = 0x1234;
      else  *bios_post = 0;
      boot();
}
 
#ifdef TEST
 
#include <stdio.h>
 
void main(void)
{
      puts("The computer should do a cold start");
      reboot(0);
}
 
#endif /* TEST */
