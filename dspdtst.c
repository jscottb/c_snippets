/*
**  Compiler I/O benchmarks
**  public domain by Dave Knapp & Bob Stout
*/

#include <stdio.h>
#include <conio.h>
#include <dos.h>

typedef unsigned long dword;

#ifdef M_I86      /* Identifier for MSC, QC, Watcom, or ZTC */

 #ifndef __ZTC__
  #include <graph.h>

  #ifndef __WATCOMC__
   #ifdef _MSC_VER
    #define LOGFILE "dspdtst.msc"
   #else
    #define LOGFILE "dspdtst.qc"
   #endif

//   #define MK_FP(seg,off) ((void far *)(((dword)(seg)<<16)|(off)))
  #else
   #define LOGFILE "dspdtst.wc"
  #endif  /* not Watcom   */

  #define cputs(s) _outtext((char _far *)(s))
  #define gotoxy(col,row) _settextposition(row,col)

 #else   /* if ZTC       */

  #include <disp.h>

  #define cputs(s) disp_puts(s "\n")
  #define cprintf(s) disp_printf(s "\n")
  #ifdef __SC__
   #define LOGFILE "dspdtst.sc"
   #define gotoxy(col,row) __emit__(0xb2,col-1,0xb6,row-1,0xb7,0,0xb4,2,0xcd,0x10)
  #else
   #define LOGFILE "dspdtst.ztc"
   #define gotoxy(col,row) asm(0xb2,col-1,0xb6,row-1,0xb7,0,0xb4,2,0xcd,0x10)
  #endif

 #endif  /* if ZTC       */
#else
 #ifdef __BORLANDC__
  #define LOGFILE "dspdtst.bc"
 #else
  #define LOGFILE "dspdtst.tc"
 #endif
#endif  /* if TC        */

dword far *bios_time = (dword far *)(0x0040006c);
dword time1,time2,time3,time4,time5,time6;

void main(void)
{
        int i;
        FILE *log = stdout, *nulfile;

#ifdef __ZTC__
        disp_open();
#endif
        nulfile = fopen("NUL", "w");
        time1 = *bios_time;
        for(i = 1; i < 1000; i++)
        {
                gotoxy(10,5);
                puts("puts      test.");
                puts("this is the second line.\n");
        }
        time1 = *bios_time - time1;
        time2 = *bios_time;
        for(i = 1; i < 1000; i++)
        {
                gotoxy(10,5);
                printf("printf    test.\n");
                printf("this is the second line.\n");
        }
        time2 = *bios_time - time2;
        time3 = *bios_time;
        for(i = 1; i < 1000; i++)
        {
#ifdef __ZTC__
                disp_move(4,9);
                cputs("d_puts    test.");
#else
                gotoxy(10,5);
 #if defined(M_I86) && !defined(__WATCOMC__)
                cputs("_outtext  test.\r\n");
 #else
                cputs("cputs     test.\r\n");
 #endif
#endif
                cputs("this is the second line.");
        }
        time3 = *bios_time - time3;
        time4 = *bios_time;
        for(i = 1; i < 1000; i++)
        {
#ifdef __ZTC__
                disp_move(4,9);
                cprintf("d_printf  test.");
#else
                gotoxy(10,5);
                cprintf("cprintf   test.\r\n");
#endif
                cprintf("this is the second line.");
        }
        time4 = *bios_time - time4;
        time5 = *bios_time;
        for(i = 1; i < 1000; i++)
        {
                fputs("fputs     test.\n", nulfile);
                fputs("this is the second line.\n", nulfile);
        }
        time5 = *bios_time - time5;
        time6 = *bios_time;
        for(i = 1; i < 1000; i++)
        {
                fprintf(nulfile, "fprintf   test.\n");
                fprintf(nulfile, "this is the second line.\n");
        }
        time6 = *bios_time - time6;

#ifdef __ZTC__
        disp_close();
#endif
        log = fopen(LOGFILE, "w");
        fputs("Times for 1000 iterations:\n\n", log);
        fprintf(log, "puts     %10.3f seconds\n", (double)time1 * .054945);
        fprintf(log, "printf   %10.3f seconds\n", (double)time2 * .054945);
#ifndef __ZTC__
 #if defined(M_I86) && !defined(__WATCOMC__)
        fprintf(log, "_outtext %10.3f seconds\n", (double)time3 * .054945);
 #else
        fprintf(log, "cputs    %10.3f seconds\n", (double)time3 * .054945);
 #endif
        fprintf(log, "cprintf  %10.3f seconds\n", (double)time4 * .054945);
#else
        fprintf(log, "d_puts   %10.3f seconds\n", (double)time3 * .054945);
        fprintf(log, "d_printf %10.3f seconds\n", (double)time4 * .054945);
#endif
        fprintf(log, "fputs    %10.3f seconds\n", (double)time5 * .054945);
        fprintf(log, "fprintf  %10.3f seconds\n", (double)time6 * .054945);
        fclose(log);
}
