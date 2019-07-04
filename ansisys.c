/*****************************************************************************
 * 
 * program that detects the presence (or absence) of an ANSI device driver.
 *
 * Returns:
 *
 * errorlevel 0: Ansi devicedriver not detected.
 * errorlevel 1: Ansi devicedriver detected.
 *
 *****************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <conio.h>



/********************************** print () *********************************
 *
 * A dum print string routine
 *
 *****************************************************************************
 */

void print(char *p)
{
      while(*p)
            putchar(*p++);
      fflush(stdout);                 /* necessary for ZTC                  */

}     /* print () */

/********************************** main () **********************************
 *
 * Detect whether ANSI.SYS is present and return 1 if so, else returns 0
 *
 *****************************************************************************
 */

int main(void)
{
      char buffer [31];               /* temporary buffer                   */
      int  nr=0;                      /* counter                            */

      print("\x1b[6n\r      \r");     /* ask for ansi device report         */

      while ((0 !=kbhit()) && (nr<30))/* read whatever input is present     */
            buffer[nr++] = (char)getch();

      buffer[nr]='\0';                /* zero terminate string              */

      if (strstr(buffer, "\x1b["))    /* check precense of device report    */
            return 1;                 /* signal ANSI.SYS present            */
      else  return 0;                 /* signal ANSI.SYS not present        */


}  /* main ()  */

/********************************** end *************************************/
