/***************************************************
 *      function : copy                            *
 *      purpose  : copy one file                   *
 *                                                 *
 *      arguments: path to source 'fromDir',       *
 *                 path to target 'toDir',         *
 *                 filename to copy 'fname'        *
 *                                                 *
 *      returns  : nothing                         *
 *                                                 *
 *      By       :  Peter Yard (29 May 1991)       *
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

void pmerge(char *path, char *drive, char *dir, char *fname, char *ext);

#define STDOUT fileno(stdout)

void copy(char *fromDir, char *fname, char *toDir)
{
      FILE    *nul;       /* nul will redirect stdout to DOS 'nul' */
      char    from[FILENAME_MAX], to[FILENAME_MAX], comd[128];
      int     bytesRead, oldStdout;

      /* Create the strings to describe the paths                  */

      pmerge(from, NULL, fromDir, fname, NULL);
      pmerge(to, NULL, toDir, fname, NULL);

      /* Construct 'comd' string which is a dos command for a copy */

      strcpy(comd, "copy ");
      strcat(comd, from); strcat(comd, " ");
      strcat(comd, to);

      /* Redirect stdout to a nul file, kills output to the screen */

      nul = fopen("NUL", "w");
      oldStdout = dup(STDOUT);
      dup2(fileno(nul), STDOUT);
      fclose(nul);

      system(comd);           /* COPY file */

      /* Restore stdout and close nul file */

      dup2(oldStdout, STDOUT);
      close(oldStdout);

      /* Display file source and target,      */
      /* otherwise comment out the next line. */

      printf("\n%s copied to %s",from,to);
}
