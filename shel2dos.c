/*
**  SHEL2DOS.C - Shell to DOS from a running program
**
**  Original Copyright 1989-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

int shell_to_DOS(void)
{
      char *comspec, prompt[256], *oldprompt;
      int retval;

      comspec = getenv("COMSPEC");
      if(comspec == NULL)
            comspec = "COMMAND.COM";     /* Better than nothing... */

      sprintf(prompt, "PROMPT=[Type EXIT to return to program]\r\n%s",
            oldprompt = getenv("PROMPT"));
      putenv(prompt); 

      retval = spawnlp(0, comspec, comspec, NULL);

      sprintf(prompt, "PROMPT=%s", oldprompt);
      putenv(prompt);

      return retval;
}

#ifdef TEST

#include <stdio.h>

void main(void)
{
      int retval = shell_to_DOS();

      printf("shell_to_DOS() returned %d\n", retval);

      retval = shell_to_DOS();
      printf("shell_to_DOS() returned %d\n", retval);
}

#endif
