/*
**  demo code for converting Pascal strings to/from C strings
**
**  public domain by Bob Stout
*/

#include <string.h>

typedef unsigned char UCHAR;

#define P2Cconvert(s) {UCHAR n = *(s); memmove((s), &(s)[1], n); s[n] = '\0';}
#define C2Pconvert(s) {int n = strlen(s); memmove(&(s)[1], (s), n); *(s) = n;}

#if (0)                             /* Demo code fragment follows */

      char string[81];

      fgets(string, 81, inFile);    /* get 80-char pascal string  */
      P2Cconvert(string);           /* convert it in place        */
      C2Pconvert(string);           /* convert back               */

#endif 
