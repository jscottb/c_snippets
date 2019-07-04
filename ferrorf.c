/*  FERRORF.C
**  Prints error message with printf() formatting syntax, then a colon,
**  then a message corressponding to the value of errno, then a newline.
**  Output is to filehandle.
**
**  Public Domain by Mark R. Devlin, free usage is permitted.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
 
int ferrorf(FILE *filehandle, const char *format, ...)
{
    int vfp, fp;
    va_list vargs;
 
    vfp = fp = 0;
    va_start(vargs, format);
    vfp = vfprintf(filehandle, format, vargs);
    va_end(vargs);
    fp = fprintf(filehandle, ": %s\n", sys_errlist[errno]);
    return ((vfp==EOF || fp==EOF) ? EOF : (vfp+fp));
}
