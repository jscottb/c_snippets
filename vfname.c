/*
**  VFNAME.C
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>

#ifdef TRUE
 #undef TRUE
#endif
#ifdef FALSE
 #undef FALSE
#endif
#ifdef ERROR
 #undef ERROR
#endif

enum LOGICAL {ERROR = -1, SUCCESS, FALSE = 0, TRUE};

#if defined(__TURBOC__)
  #include <dir.h>
#endif
#if !defined( MAXFILE )
  #define MAXFILE 9
#endif

#define NUL '\0'

/*
**  Prototypes
*/

int valid_fname  (char *fname, int wild_check);

/*
**  valid_fname.c
**
**  Verifies whether a filename is valid or invalid without
**  altering the passed filename itself.
**
**  Note that only filenames are validated. Path and drive specs
**  need to be separately validated. See FLN_FIX.C in SNIPPETS.
**
**  Arguments: 2 - fname = a char array MAXFILE long
**                 wild_check: 0 means wildcard use okay
**                             any other value means test for
**                             wildcards which are not acceptable
**
**  Returns:   ERROR   - fname is invalid
**             SUCCESS - fname is valid
**
**  Side effects: none
**
**  Speed: 1) Turbo Profiler rates valid_fname at 0.0004 sec/call
**            on an Intel 80286.
**         2) Token testing from both ends to center yields a slight
**            improvement.
**
**  Notes: Space, ASCII character 32, is a special case. Dos will
**         write a filename or volume label that includes a space.
**         Getting access to that file, afterwards, is not always
**         easy :) For my purposes, space is an invalid filename
**         token. You? You're on your own :)
**
**         Uses strnicmp() and stricmp(), non-ISO/ANSI, but available on
**         all DOS C compilers (MSC, BC++, SC++ WC, etc.)
**
**  Revisions: 1) Dropped str2upper after comment by David Johnson
**                on 07-17-93
**             2) Added [] to token list after comment by Ed
**                Kowalski on 07-17-93
**             3) Added lpt1-lpt3, com1-com4 and clock$ to
**                invalid name list after comment by Ed
**                Kowalski on 07-17-93
**             4) Eliminated double exit points after my own
**                comment to Bob Stout :) on 07/22/1993
**             5) Revisions to detect DOS extension errors on 03/13/94   
**
**  Public domain by Sid Rogers and Bob Stout
**
*/

int valid_fname(char *fname, int wild_check)
{
      /* invalid filename tokens */

      static char invalid_tokens[] = "\0 ,;:|\\/<>\"+=[]*?";
      static int  itoklen = sizeof(invalid_tokens) - 1;

      /* invalid file names -- even with extension .xxx */

      static char *invalid_3lnam[]={"AUX","CON","PRN","NUL","COM",NULL};

      /* other invalid file & directory names */

      static char *invalid_4lnam[]={"LPT1","LPT2","LPT3","COM1",
                                    "COM2","COM3","COM4",NULL};

      static char *invalid_6lnam = "CLOCK$";

      int   num_toks, fl, i, j, k, proceed = 0;
      char *p;

      /* Handle the critical stuff first  */

      for (i = 0; invalid_3lnam[i]; ++i)
      {
            if (SUCCESS == strnicmp(fname, invalid_3lnam[i], 3))
                  proceed = ERROR;
      }

      /* Handle extensions next           */

      if (ERROR != proceed && NULL != (p = strchr(fname, '.')))
      {
            if (3 < strlen(p+1) || NULL != strchr(p+1, '.'))
                  proceed = ERROR;
            if (8 < (p - fname))
                  proceed = ERROR;
      }

      if (ERROR != proceed)
      {
            if (p)
                  *p = NUL;

            for (i = 0; invalid_4lnam[i]; ++i)
            {
                  if (SUCCESS == stricmp(fname, invalid_4lnam[i]))
                        proceed = ERROR;
            }

            if (SUCCESS == stricmp(fname, invalid_6lnam))
                  proceed = ERROR;
            if (p)
                  *p = '.';
            else if (8 < strlen(fname))
                  proceed = ERROR;
      }

      fl = strlen(fname);

      /* process filename for invalid tokens */

      if (ERROR != proceed)
      {
            if (wild_check)
                  num_toks = itoklen;                 /* wildcards invalid */
            else  num_toks = itoklen - 2;             /* wildcards ok      */

            for (i = -1, j = 0; i < 0 && j < num_toks; j++)
            {
                  for (k = 0; k < fl; k++)
                        if(invalid_tokens[j] == fname[k])
                              i=j;
            }
            if (i >= 0)
                  proceed = ERROR;
      }
      return proceed; /* single exit point */
}

#ifdef TEST

/*
**  Revised function test - Performs standard tests and then validates
**  filenames passed on the command line.
*/

main(int argc, char *argv[])
{
      static char *name_test[]= {"aaa","aux","con","prn","nul","lpt1", "lpt2",
                                 "lpt3","com1","com2","com3", "com4","bbbb",
                                 "clock$","com.c", "cccccc",NULL};

      static char *token_test[]={"00fname.","01 fname","02fname,", "03fname[",
                                 "04fname;","05fname:", "06fname|","07fname/",
                                 "08fname<", "09fname>","10fname+","11fname=",
                                 "12fname\\","13fname\"","14fname]",
                                 "15fname*", "16fname?","filename", NULL};

      char fname[MAXFILE];
      int i;

      for (i = 0; name_test[i]; ++i)
      {
            strcpy(fname,name_test[i]);
            printf("%6s is %s\n",fname,
                  valid_fname(fname,0) ? "INvalid" : "Valid");
      }

      puts("\nHit a key");
      getch();

      puts("\n[Wildcards not allowed]\n");
      for (i = 0; token_test[i]; ++i)
      {
            strcpy(fname,token_test[i]);
            printf("%s is %s\n",fname,
                  valid_fname(fname,1) ? "INvalid" : "Valid");
      }

      puts("\nHit a key");
      getch();

      puts("\n[Wildcards allowed]\n");
      for (i = 0; token_test[i]; ++i)
      {
            strcpy(fname,token_test[i]);
            printf("%s is %s\n",fname,
                  valid_fname(fname,0) ? "INvalid" : "Valid");
      }

      puts("\nHit a key");
      getch();

      while (--argc)
      {
            strcpy(fname, *(++argv));
            printf("%s is %s\n",fname,
                  valid_fname(fname,1) ? "INvalid" : "Valid");
      }
      return 0;
}
#endif
