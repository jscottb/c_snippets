/*****************************************************************/
/**   CURSOR()                                                  **/
/**   ARGUMENTS: A char variable identifiny what to do with     **/
/**              the cursor.                                    **/
/**   RETURN: none                                              **/
/**                                                             **/
/**   DESCRIPTION:  This function receives a character which    **/
/**                 tells it to do one of several things.       **/
/**                 Turn the cursor on or off, or save the      **/
/**                 cursor positon, or restore the position.    **/
/**                                                             **/
/**   BY Bill Wilkie, 1988                                      **/
/*****************************************************************/
 
#include <dos.h>
 
static int position;            /* global to hold cursor postion */
 
void cursor(char tmp)
{
   union REGS inregs,outregs;                   /* cpu registers */
    
   switch(tmp)
   {
      case 'h' :                                  /* CURSOR OFF */
               inregs.h.ah = 1;              /* set cursor size */
               inregs.h.ch = 0x20;  /* set bit turns cursor off */
               int86(0x10,&inregs,&outregs);
               break;
 
      case 's' :                      /* SAVE CURSOR POSITION */
               inregs.h.ah = 3; /* read cursor positon and size */
               inregs.h.bh = 0;              /* from page zero */
               int86(0x10,&inregs,&outregs);
               position = outregs.x.dx;       /* store positon */
               break;
 
      case 'r' :                     /* RESTORE CURSOR POSITON */
               inregs.h.ah = 2;         /* set cursor positon */
               inregs.h.bh = 0;              /* on page zero */
               inregs.x.dx = position; /* at this old position */
               int86(0x10,&inregs,&outregs);
               break;
 
      case 'o' :                                   /* CURSOR ON */
               inregs.h.ah = 1;     /* set cursor size */     
               inregs.h.ch = 6;     /* cursor start line */
               inregs.h.cl = 7;     /* cursor end line */
               int86(0x10,&inregs,&outregs);
               break;
    }
}
