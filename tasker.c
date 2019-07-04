/*
**  Tasker.C
**
**  public domain by David Gibbs
*/

struct ts_os_ver t_os_ver[TOT_OS];
int t_os_type;
int t_os;

const char *t_os_name[TOT_OS] = {
      "DOS",
      "OS/2 DOS",
      "DESQview",
      "Windows Std",
      "Windows 386"
      };

int get_os (void)
{
      union REGS t_regs;

      t_os_type = 0;
      t_os = 0;

      /* test for DOS or OS/2 */

      if (_osmajor < 10)
      {
            t_os_ver[DOS].maj = _osmajor;
            t_os_ver[DOS].min = _osminor;
            t_os_type = t_os_type | is_DOS;
      }
      else
      {
            t_os_type = t_os_type | is_OS2;
            t_os_ver[OS2].maj = _osmajor/10;
            t_os_ver[OS2].min = _osminor;
      }

      /* test for Windows */

      t_regs.x.ax = 0x4680;
      int86(0x2F, &t_regs, &t_regs);

      if (t_regs.x.ax == 0x0000)
      {
            t_os_ver[WINS].maj = 3;
            t_os_ver[WINS].min = 0;
            t_os_type = t_os_type | is_WINS;
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
                  t_os_type = t_os_type | is_WIN3;
                  t_os_ver[WIN3].maj = t_regs.h.al;
                  t_os_ver[WIN3].min = t_regs.h.ah;
                  break ;
            }  /* endswitch  */
      } /* endif */

      /* Test for DESQview */

      t_regs.x.cx = 0x4445;     /* load incorrect date */
      t_regs.x.dx = 0x5351;
      t_regs.x.ax = 0x2B01;     /*  DV set up call     */

      intdos(&t_regs, &t_regs);
      if (t_regs.h.al != 0xFF)
      {
            t_os_type = t_os_type | is_DV;
            t_os_ver[DV].maj = t_regs.h.bh;
            t_os_ver[DV].min = t_regs.h.bl;
      }

      if(t_os_type & is_DOS)
            t_os = DOS;

      if(t_os_type & is_WINS)
            t_os = WINS;

      if(t_os_type & is_WIN3)
            t_os = WIN3;

      if(t_os_type & is_DV)
            t_os = DV;

      if(t_os_type & is_OS2)
            t_os = OS2;

      return(t_os-1);

}

void t_slice(void)
{
      union REGS t_regs;
    
      switch (t_os)
      {
      case DOS  :
            break;

      case OS2  :
      case WIN3 :
      case WINS :
            t_regs.x.ax = 0x1680;
            int86(0x2f,&t_regs,&t_regs);
            break;

      case DV   :
            t_regs.x.ax = 0x1000;
            int86(0x15,&t_regs,&t_regs);
            break;
      } /* switch(t_os) */
}
