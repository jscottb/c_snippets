/*
**  SCRNSAVE.C - Save and restore text screen portably
**
**  public domain demo by Bob Stout
*/

#include <stdlib.h>

/*
**  Stuff from SNIPPETS courtesy of Jim Nutt
**
**  Notes: VIOopen() is called redundantly to assure that the video
**         information is always initialized. These multiple calls are benign.
**
**         Because of using VIO.OBJ, this *must* be compiled in large model!
*/

#include "vio.h"

/*
**  Save the current text screen
**
**  Arguments: None
**
**  Returns: Pointer to saved screen buffer, NULL if insufficient heap
*/

unsigned short *savescreen(void)
{
      unsigned short *vbuf;

      VIOopen();
      if (NULL == (vbuf = malloc(VIOcolumns() * VIOrows() * 2)))
            return NULL;
      VIOgetra(0, 0, VIOcolumns() - 1, VIOrows() - 1, (int _far *)vbuf);
      return vbuf;
}

/*
**  Restore a screen previously saved by savescreen()
**
**  Arguments: Buffer containing the screen to restore
**
**  Returns: Nothing
**
**  WARNING: No error checking done to verify same screen size and mode!
*/

void restorescreen(unsigned short *vbuf)
{
      VIOopen();
      VIOputr(0, 0, VIOcolumns(), VIOrows(), (int _far *)vbuf);
      free(vbuf);
}

#ifdef TEST

#include <stdio.h>
#include <conio.h>

int main(void)
{
      unsigned short *vbuf;

      VIOopen();
      if (NULL == (vbuf = savescreen()))
      {
            puts("Unable to save screen");
            return EXIT_FAILURE;
      }
      VIOclear(0, 0, VIOcolumns(), VIOrows());
      puts("Hit any key to exit");
      getch();
      restorescreen(vbuf);
      VIOclose();
      return EXIT_SUCCESS;
}

#endif /* TEST */
