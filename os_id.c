/*
**  OS_ID.C
**
**  based upon a public domain work by David Gibbs
*/

#define TEST
#define OS_ID_MAIN
#include "os_id.h"
#include <dos.h>

struct i_os_ver id_os_ver[TOT_OS];
int id_os_type;
int id_os;

const char *id_os_name[TOT_OS] = {
      "DOS",
      "OS/2 DOS",
      "DESQview",
      "Windows Std",
      "Windows 386"
      };

int get_os (void)
{
      union REGS t_regs;
      int osmajor, osminor;

      id_os_type = 0;
      id_os = 0;

      /* test for DOS or OS/2 */

      t_regs.h.ah = 0x30;
      int86(0x21, &t_regs, &t_regs);
      osmajor = t_regs.h.al;
      osminor = t_regs.h.ah;

      if (osmajor < 10)
      {
            id_os_ver[DOS].maj = osmajor;
            id_os_ver[DOS].min = osminor;
            id_os_type = id_os_type | is_DOS;
      }
      else
      {
            /* OS/2 v1.x DOS Box returns 0x0A */

            id_os_type = id_os_type | is_OS2;

            /* OS/2 v2.x DOS Box returns 0x14 */

            id_os_ver[OS2].maj = osmajor/10;
            id_os_ver[OS2].min = osminor;
      }

      /* test for Windows */

      t_regs.x.ax = 0x4680;
      int86(0x2F, &t_regs, &t_regs);

      if (t_regs.x.ax == 0x0000)
      {
            id_os_ver[WINS].maj = 3;
            id_os_ver[WINS].min = 0;
            id_os_type = id_os_type | is_WINS;
      }
      else
      {
            t_regs.x.ax = 0x1600 ;
            int86(0x2F, &t_regs, &t_regs);

            switch (t_regs.h.al)
            {
            case 0x00 :
            case 0x80 :
            case 0x01 :
            case 0xFF :
                  break;

            default   :
                  id_os_type = id_os_type | is_WIN3;
                  id_os_ver[WIN3].maj = t_regs.h.al;
                  id_os_ver[WIN3].min = t_regs.h.ah;
                  break ;
            }  /* endswitch  */
      } /* endif */

      /* Test for DESQview */

      t_regs.x.cx = 0x4445;                /* load incorrect date */
      t_regs.x.dx = 0x5351;
      t_regs.x.ax = 0x2B01;                /*  DV set up call     */

      intdos(&t_regs, &t_regs);
      if (t_regs.h.al != 0xFF)
      {
            id_os_type = id_os_type | is_DV;
            id_os_ver[DV].maj = t_regs.h.bh;
            id_os_ver[DV].min = t_regs.h.bl;
      }

      if (id_os_type & is_DOS)
            id_os = DOS;
      if (id_os_type & is_WINS)
            id_os = WINS;
      if (id_os_type & is_WIN3)
            id_os = WIN3;
      if (id_os_type & is_DV)
            id_os = DV;
      if (id_os_type & is_OS2)
            id_os = OS2;

      return(id_os);
}


#ifdef TEST

#include <stdio.h>

int main(void)
{
      int ostype = get_os();

      printf("%s version %d.%d\n",
            id_os_name[ostype],
            id_os_ver[ostype].maj,
            id_os_ver[ostype].min);

      return(0);
}

#endif
