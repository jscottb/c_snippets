/*
** ERRFIX.C - redirect stderr to some other file under MS-DOS
**
** by Bob Jarvis
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

char *usage = "ERRFIX [filename] [prog] { {parm1} {parm2} ... {parmN} }\n"
              "   Redirects stderr to another file, then invokes a program\n"
              "   which will inherit the new definition of stderr.\n\n"
              "Parameters:\n"
              "   filename (required) - the name of the file stderr should\n"
              "      be redirected to.  Output written to stderr will\n"
              "      be routed to this file instead of the console.\n"
              "   prog (required) - name of the program to be run.\n"
              "   parm1...parmN (optional) - command-line parameters needed\n"
              "      to run the program specified by the 'prog' argument.";

int main(int argc, char *argv[])
{
      char **args = argv;

      if (3 > argc)
      {
            printf(usage);
            return 1;
      }

      if (NULL != argv[argc]) /* may be a problem under some compilers */
      {
            args = malloc((argc+1) * sizeof(char *));
            if (NULL == args)
            {
                  printf("Unable to allocate storage");
                  return 2;
            }

            memcpy(args, argv, argc * sizeof(char *));

            args[argc] = NULL;
      }

      freopen(args[1], "w", stderr);

      spawnvp(0, args[2], &args[2]);

      return 0;
}
