/* CLOCK.H:  prototypes/defines for the CLOCK.C file                    */
/*
    This file written in 1990 Jonathan R. Guthrie and placed in the
    public domain
*/

int     far     startclock(int x, int y, int attr);
void    far     stopclock(void);

#define CLOCK_OK        0   /* Clock was installed properly             */
#define CLOCK_ERR_INST  -1  /* Clock is already installed               */
#define CLOCK_ERR_OOS   -2  /* Clock would be off the screen            */


/* CLOCK.C:  An on-screen clock generator                               */
/*
    This file written in 1990 Jonathan R. Guthrie and placed in the
    public domain
*/

#include    <stdlib.h>
#include    <conio.h>
#include    <time.h>
#include    <dos.h>
#include    "clock.h"

#define CLOCK       0x1c
#define TRUE        1
#define FALSE       0

/* Now, the stuff needed for the for the on-screen clock                */

static  void    interrupt   (*oldvector)(void);
static  void    interrupt   do_clock(void);
static  void    setstr(char *, int, size_t);

static  char    timestuff[22], hours, oddfives, ticks, ticklimit;

static  int     clockx, clocky, clockattr, installed = FALSE;

int     far     startclock(int x, int y, int attr)
{
      time_t  temptime;
      struct  tm  *struct_time;
      int     bigx;
      struct  text_info   r;

      /* The clock starting routine */

      /* First, see if it's already installed */

      if(installed)
            return  CLOCK_ERR_INST;
      else  installed = TRUE;

      /* Now, set assorted important module constants */

      clockx = x;
      clocky = y;
      clockattr = attr;

      gettextinfo(&r);

      if((clockx < 0) || (clockx > r.screenwidth - 10) ||
         (clocky < 0) || (clocky > r.screenheight))
      {
            installed = FALSE;
            return CLOCK_ERR_OOS;
      }

      /* Now, set the program's clock */

      setstr(timestuff, clockattr, 22);

      time(&temptime);
      struct_time = localtime(&temptime);

      oddfives    = 0;
      ticklimit   = 17;
      hours         = (struct_time->tm_hour + 11) % 12 + 1;
      timestuff[0]  = (hours > 9) ? '1' : ' ';
      timestuff[2]  = '0' + hours % 10;
      timestuff[4]  = ':';
      timestuff[6]  = '0' + struct_time->tm_min / 10;
      timestuff[8]  = '0' + struct_time->tm_min % 10;
      timestuff[10] = ':';
      timestuff[12] = '0' + struct_time->tm_sec / 10;
      timestuff[14] = '0' + struct_time->tm_sec % 10;
      timestuff[16] = ' ';
      timestuff[18] = (struct_time->tm_hour > 11) ? 'P' : 'A';
      timestuff[20] = 'M';

      /* Now, initialize the clock as displayed on the screen */

      puttext(clockx, clocky, clockx+10, clocky, timestuff);

      /* Finally, set the vector to point to the clock routine */

      disable();
      oldvector = getvect(CLOCK);
      setvect(CLOCK, do_clock);
      enable();
      return  CLOCK_OK;
}

static  void    interrupt   do_clock(void)
{
      ++ticks;
      if(ticks > ticklimit)   /* Then, it's time to update the seconds */
      {
            ticks = 0;

            /* First, handle the fractional Hz part */

            ++oddfives;
            if (5 == oddfives)
            {
                  oddfives = 0;
                  ticklimit = 18;
            }
            else
            {
                  ticklimit = 17;
            }
   
            /* Now, handle the seconds count */

            ++timestuff[14];

            if (timestuff[14] > '9')
            {
                  timestuff[14] = '0';

                  /* Now, handle the tens of seconds count */

                  ++timestuff[12];
                  if (timestuff[12] > '5')
                  {
                        timestuff[12] = '0';

                        /* Now, handle the minutes count */

                        ++timestuff[8];
                        if (timestuff[8] > '9')
                        {
                              timestuff[8] = '0';

                              /* Now, handle the ten minutes count */

                              ++timestuff[6];
                              if (timestuff[6] > '5')
                              {
                                    timestuff[6] = '0';

                                    /* Now, handle the hours count */

                                    ++hours;
                                    if(12 == hours)
                                          if ('P' == timestuff[18])
                                                timestuff[18] = 'A';
                                          else  timestuff[18] = 'P';

                                    if(hours > 12)
                                          hours = 1;

                                    timestuff[0] = (hours > 9) ? '1' : ' ';
                                    timestuff[2] = '0' + hours % 10;
                              }
                        }
                  }
            }

            /* Now, update the display */

            puttext(clockx, clocky, clockx+10, clocky, timestuff);
      }
}

void    far     stopclock(void)
{
      if(installed)
      {
            disable();
            setvect(CLOCK, oldvector);
            enable();
            installed = FALSE;
      }
}

static  void    setstr(char *s, int ch, size_t n)
{
      size_t  i;
    
      for(i=0 ; i<n ; ++i)
      {
            s[i] = ch;
      }

      s[i] = '\0';
}
