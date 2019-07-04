/*
**  GETOPTS.C - Universal command line options parser
**
**  Original Copyright 1993 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is hereby donated to the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portable.h"
#include "getopts.h"

#define NUL '\0'
#define MAX_XARGS 512

int   xargc;
char *xargv[MAX_XARGS];

/*
**  getopts()
**
**  Parameters: 1 - argc from main()
**              2 - argv from main()
**              3 - your program's options[] array
**
**  Returns: Number of options specified or -1 if error
**
**  Note: Your program should declare the global options[] array which
**        specifies all options recognized by getopts().
*/

int getopts(int argc, char *argv[])
{
      int i, count, argidx = 0;
      char *argp;
	FILE *argfile;
	char argline[256];
      struct Option_Tag *ptr;

      xargc = argc;
      xargv[argidx++] = argv[0];
      for (i = 1, count = 0; i < argc; ++i)
      {
            if (strchr("-/", argv[i][0]) && !strchr("-/", argv[i][1]))
            {
                  /*
                  ** Found a switch - If the 2nd character is also a switch
                  ** character. If so, then it's a literal and is skipped
                  */

                  if (strchr("-/", argv[i][1]))
                        continue;

                  for (ptr = options; ptr->buf; ++ptr)
                  {
                        if ((int)argv[i][1] == ptr->letter) switch (ptr->type)
                        {
                        case Boolean_Tag:
                              if ('-' == argv[i][2])
                                    *((Boolean_T *)(ptr->buf)) = FALSE;
                              else  *((Boolean_T *)(ptr->buf)) = TRUE;
                              ++count;
                              --xargc;
                              break;

                        case Word_Tag:
                              sscanf(&argv[i][2], "%hd", (short *)(ptr->buf));
                              ++count;
                              --xargc;
                              break;

                        case DWord_Tag:
                              sscanf(&argv[i][2], "%ld", (long *)(ptr->buf));
                              ++count;
                              --xargc;
                              break;

                        case Double_Tag:
                              sscanf(&argv[i][2], "%lg", (double *)(ptr->buf);
                              ++count;
                              --xargc;
                              break;

                        case String_Tag:
                              strcpy(ptr->buf, &argv[i][2]);
                              ++count;
                              --xargc;
                              break;

                        default:
                              return ERROR;
                        }
                  }
            }
            else                          /* It must be a file name     */
            {
                  DOSFileData ffblk;

                  /* Set argp to point to the filename                  */

                  if (strchr("-/", argv[i][0]))
                        argp = &argv[i][1];
                  else  argp =  argv[i];

                  /* If no wildcards, just copy it */

                  if (!strchr(argp, '*') && !strchr(argp, '?'))
                  {
                        xargv[argidx++] = argp;
                        continue;
                  }

                  /* Expand wildcards, if possible                      */

                  if (0 == FIND_FIRST(argp, 0xff, &ffblk))
                  {
                        char path[FILENAME_MAX], *p;

                        /* Save the path for re-attachment              */

                        if (NULL == (p = strrchr(argp, '\\')))
                              p = strrchr(argp, '/');
                        if (p)
                        {
                              char ch = *p;

                              *p = NUL;
                              strcat(strcpy(path, argp), "\\");
                              *p = ch;
                        }
                        else  *path = NUL;
                        --xargc;
                        do
                        {                             
                              xargv[argidx] = malloc(strlen(ffblk.name)
                                    + strlen(path) + 2);
                              strcat(strcpy(xargv[argidx], path), ffblk.name);
                              ++argidx;
                              ++xargc;
                        
                        } while (0 == FIND_NEXT(&ffblk));
                  }
            }
      }
      return count;
}

#ifdef TEST

#include <stdlib.h>

Boolean_T test1 = TRUE, test2 = FALSE;
int   test3     = -37;
long  test4     = 100000L;
char  test5[80] = "Default string";

struct Option_Tag options[] = {
      {'A',  Boolean_Tag, &test1 },             /* Valid options        */
      {'B',  Boolean_Tag, &test2 },
      {'C',  Word_Tag,    &test3 },
      {'D',  DWord_Tag,   &test4 },
      {'E',  String_Tag,   test5 },
      {'\0', ERROR,        NULL  }              /* Terminating record   */
};

#define TFprint(v) ((v) ? "TRUE" : "FALSE")

int main(int argc, char *argv[])
{
      int i;

      printf("Defaults:\ntest1 = %s\ntest2 = %s\ntest3 = %d\ntest4 = %ld\n"
            "test5 = \"%s\"\n\n", TFprint(test1), TFprint(test2), test3,
            test4, test5);

      printf("getopts() returned %d\n", getopts(argc, argv));

      printf("Options are now:\ntest1 = %s\ntest2 = %s\ntest3 = %d\n"
            "test4 = %ld\ntest5 = \"%s\"\n\n", TFprint(test1),
            TFprint(test2), test3, test4, test5);

      puts("Hit any key to continue");
      getch();
      for (i = 0; i < xargc; ++i)
            printf("xargv[%d] = \"%s\"\n", i, xargv[i]);
      printf("\nxargc = %d\n", xargc);
      return 0;
}

#endif
