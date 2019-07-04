/* editgets.c - line input w/editing                                        */
/* this code is released to the public domain                               */
/* written by Jon Burchmore                                                 */
/* modifications & enhancements by Bob Stout                                */

/* This is as close to ANSI compliant C that I could come, but it was made  */
/* on an IBM compatable computer, so I designed it for that platform.       */
/* If you're porting it to another computer type, please note how the IBM   */
/* passes enhanced keys.  First, it sends an ASCIIZ (character 0), then a   */
/* standard character.  Anyway, what the switch() statement does is check   */
/* to see if there WAS a zero sent, and if there wasn't, it just "falls"    */
/* through to the default, which handles normal characters.                 */

/* The conio header file provides the getch() function, which returns a     */
/* single character from the KEYBOARD, not stdin, and waits if it must.     */
/* It is be possible to re-write this function for a computer besides an    */
/* IBM PC.                                                                  */

/* It would be possible to check the variable insert, and if it's on, make  */
/* the cursor large, and if it's off, make the cursor small, but my primary */
/* goal is portability, not fancy add-ons                                   */

/* Pardon the lack of comments.  I'm a coder, not an author.  Besides, if   */
/* you can't understand this, DON'T USE IT! (Words to live by)              */

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#undef min
#define min(x,y) (((x) <= (y)) ? (x) : (y))

#define NUL     0x00
#define ESC     0x1B
#define LEFT    0x4B
#define RIGHT   0x4D
#define HOME    0x47
#define END     0x4F
#define INSERT  0x52
#define DELETE  0x53
#define BACKSPC 0x08
#define ENTER   0x0D
#define CTLEND  0x75
#define CTLHOME 0x77
#define CTLRT   0x74
#define CTLLFT  0x73

/*
**  Password mode - '*' is echoed for all characters, only ESC, ENTER,
**  BACKSPC, and CTLHOME are active.
*/

int password_mode = 0;

/*
**  Aruments: 1) Buffer to receive string
**            2) Size of buffer
**            3) Default string
*/

int jgets(char *s, int maxlen, char *string)
{
      char temp[500];
      int insert = 1, done = 0, pos, len, i, j, c, zeroflag;

      if (NULL == string)
            string = "";

      if (0 != (pos = len = strlen(string)))
            strncpy(temp, string, min(len, maxlen));

      for (i = 0; i < maxlen; ++i)
      {
            if (NUL == *string)
                  putchar('_');
            else  putchar(*string++);
      }
      for (i = 0; i < (maxlen - len); ++i)
            putchar(BACKSPC);

      while (!done)
      {
            zeroflag = 0;
            if ((c = getch()) == 0)
            {
                  zeroflag = 1;
                  c = getch();
            }
            switch (c)
            {
            case ESC :
                  if (len == 0)
                        break;
                  if (pos != len)
                  {
                        for (i = pos; i < len; i++)
                              putch('_');
                        for (i = len; i >= 0; i--)
                        {
                              putch(BACKSPC);
                              putch('_');
                              putch(BACKSPC);
                        }
                        pos = len = 0;
                        break;
                  }

            case LEFT :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        if (pos == 0)
                              break;
                        pos--;
                        putch(BACKSPC);
                        break;
                  }

            case RIGHT :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        if (pos == len)
                              break;
                        if (pos != maxlen)
                        {
                              putch(temp[pos]);
                              pos++;
                        }
                        break;
                  }

            case HOME :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        while (pos-- > 0)
                              putch(BACKSPC);
                        pos = 0;
                        break;
                  }

            case END :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        while (pos < len)
                              putch(temp[pos++]);
                        break;
                  }

            case INSERT :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        insert = (!(insert));
                        break;
                  }

            case DELETE :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        if (pos == len)
                              break;
                        for (i = pos; i < len; i++)
                              temp[i] = temp[i + 1];
                        len--;
                        for (i = pos; i < len; i++)
                              putch(temp[i]);
                        putch('_');
                        for (i = len + 1; i > pos; i--)
                              putch(BACKSPC);
                        break;
                  }

            case BACKSPC :
                  if (c == BACKSPC)
                  {
                        if (pos == 0)
                              break;
                        if (pos != len)
                        {
                              for (i = pos - 1; i < len; i++)
                                    temp[i] = temp[i + 1];
                              pos--;
                              len--;
                              putch(BACKSPC);
                              for (i = pos; i < len; i++)
                                    putch(temp[i]);
                              putch('_');
                              for (i = len; i >= pos; i--)
                                    putch(BACKSPC);
                        }
                        else
                        {
                              putch(BACKSPC);
                              putch('_');
                              putch(BACKSPC);
                              pos = --len;
                        }
                        break;
                  }

            case ENTER :
                  if (c == ENTER)
                  {
                        done = 1;
                        break;
                  }

            case CTLEND :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        for (i = pos; i < len; ++i)
                              putch('_');
                        for (i = pos; i < len; ++i)
                              putch(BACKSPC);
                        len = pos;
                        break;
                  }

            case CTLHOME :
                  if (zeroflag)
                  {
                        if (pos == 0)
                              break;
                        if (pos != len)
                        {
                              while (0 != pos)
                              {
                                    for (i = pos - 1; i < len; i++)
                                          temp[i] = temp[i + 1];
                                    pos--;
                                    len--;
                                    putch(BACKSPC);
                                    for (i = pos; i < len; i++)
                                          putch(temp[i]);
                                    putch('_');
                                    for (i = len; i >= pos; i--)
                                          putch(BACKSPC);
                              }
                        }
                        else
                        {
                              while (0 != pos)
                              {
                                    putch(BACKSPC);
                                    putch('_');
                                    putch(BACKSPC);
                                    pos = --len;
                              }
                        }
                        break;
                  }

            case CTLRT :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        do
                        {
                              if (pos == len)
                                    break;
                              if (pos != maxlen)
                              {
                                    putch(temp[pos]);
                                    pos++;
                              }
                        } while (isspace(temp[pos]));
                        do
                        {
                              if (pos == len)
                                    break;
                              if (pos != maxlen)
                              {
                                    putch(temp[pos]);
                                    pos++;
                              }
                        } while (!isspace(temp[pos]));
                        break;
                  }

            case CTLLFT :
                  if (zeroflag)
                  {
                        if (password_mode)
                              break;
                        do
                        {
                              if (pos == 0)
                                    break;
                              pos--;
                              putch(BACKSPC);
                        } while (isspace(temp[pos]));
                        do
                        {
                              if (pos == 0)
                                    break;
                              pos--;
                              putch(BACKSPC);
                        } while (!isspace(temp[pos]));
                        break;
                  }

            default :
                  if (zeroflag)
                        break;
                  if (c == 0 || pos == maxlen)
                        break;
                  if ((!(insert)) || pos == len)
                  {
                        temp[pos++] = (char)c;
                        if (pos > len) len++;
                        if (password_mode)
                              putch('*');
                        else  putch(c);
                  }
                  else
                  {
                        if (len == maxlen)
                              break;
                        for (i = len++; i >= pos; i--)
                              temp[i + 1] = temp[i];
                        temp[pos++] = (char)c;
                        if (password_mode)
                              putch('*');
                        else  putch(c);
                        for (i = pos; i < len; i++)
                              putch(temp[i]);
                        for (i = len; i > pos; i--)
                              putch(BACKSPC);
                  }
            }
      }
      temp[len] = '\0';
      strcpy(s, temp);
      return len;
}

#ifdef TEST

void main(void)
{
      char mystring[60];

      memset(mystring, 0, 60);
      fputs("Enter any string: ", stdout);
      jgets(mystring, 60, "This is a test");
      puts("");
      printf("editgets() returned:\n%s\n", mystring);

      password_mode = 1;
      memset(mystring, 0, 60);
      fputs("Enter any password: ", stdout);
      jgets(mystring, 50, NULL);
      puts("");
      printf("editgets() returned:\n%s\n", mystring);
}

#endif
