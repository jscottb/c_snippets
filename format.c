/*
**  FORMAT.C - Use DOS FORMAT to format a diskette
**
**  Original Copyright 1992 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/
 
#include <stdio.h>
#include <stdlib.h>
 
enum {ERROR = -1, SUCCESS};
 
/*
**  format
**
**  Formats a specified floppy disk with optional switches.
**
**  Parameters: 1 - Drive letter ('A', 'B', ...) to format
**              2 - Formatting switches in FORMAT.COM format, e.g. "/4"
**              3 - Volume label
**
**  Returns: SUCCESS or ERROR
*/
 
int format(char drive, char *switches, char *vlabel)
{
      char command[128], fname[13];
      FILE *tmpfile;
 
      tmpnam(fname);
      if (NULL == (tmpfile = fopen(fname, "w")))
            return ERROR;                       /* Can't open temp file */
      fprintf(tmpfile, "\n%s\nN\n", vlabel);
      fclose(tmpfile);
 
      sprintf(command, "format %c: /V %s < %s > NUL", drive, switches, fname);
 
      system(command);
 
      remove(fname);
 
      return SUCCESS;
}
 
#ifdef TEST
 
void main(void)
{
      int retval = format((char)'a', "/4", "dummy_test");
 
      printf("format() returned %d\n", retval);
}
 
#endif
