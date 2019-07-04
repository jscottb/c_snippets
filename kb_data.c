/* by: Dan Kozak */

#include <stdio.h>

#ifdef __TURBOC__
 #define _far far
#endif
 
typedef struct                     /* Keyboard status structure */
 {
  unsigned int
  right_shift_down  : 1,           /* Right Shift key depressed */
  left_shift_down   : 1,            /* Left Shift key depressed */
  ctrl_shift_down   : 1,                  /* Ctrl key depressed */
  alt_shift_down    : 1,                   /* Alt key depressed */
  scroll_on         : 1,                   /* Scroll Lock is on */
  num_on            : 1,                      /* Num Lock is on */
  caps_on           : 1,                     /* Caps Lock is on */
  ins_on            : 1,              /* Insert state is active */
  filler            : 3,           /* Filler for word alignment */
  ctrl_numloc       : 1,                   /* Suspend key is on */
  scroll_down       : 1,           /* Scroll Lock key depressed */
  num_down          : 1,              /* Num Lock key depressed */
  caps_down         : 1,             /* Caps Lock key depressed */
  ins_down          : 1;                /* Insert key depressed */
 } biosshiftstate;
 
biosshiftstate _far *kbd_status = (biosshiftstate _far *) 0x00000417L;
 
main()
{
      while(1)
      {
            printf("right_shift_down = %d\n",kbd_status->right_shift_down);
            printf("left_shift_down = %d\n",kbd_status->left_shift_down);
            printf("ctrl_shift_down = %d\n",kbd_status->ctrl_shift_down);
            printf("alt_shift_down = %d\n",kbd_status->alt_shift_down);
            printf("scroll_on = %d\n",kbd_status->scroll_on);
            printf("num_on = %d\n",kbd_status->num_on);
            printf("caps_on = %d\n",kbd_status->caps_on);
            printf("ins_on = %d\n",kbd_status->ins_on);
            printf("filler = %d\n",kbd_status->filler);
            printf("ctrl_numloc = %d\n",kbd_status->ctrl_numloc);
            printf("scroll_down = %d\n",kbd_status->scroll_down);
            printf("num_down = %d\n",kbd_status->num_down);
            printf("caps_down = %d\n",kbd_status->caps_down);
            printf("ins_down = %d\n",kbd_status->ins_down);
      }
      return 0;
}
