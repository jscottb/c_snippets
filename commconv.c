/*
 * COMMCONV.C
 * Change C++ -comments to C-comments
 *
 * Public domain by Jari Laaksonen (2:221/105.11), 22 Dec 1992
 */

#include <stdio.h>

int main (int argc, char **argv)
{
  int  Char, cpp_comment = 0, c_comment = 0, in_string = 0;
  char CannotOpen[] = "\nCannot open %s\n\n";
  FILE *InFile, *OutFile = stdout;

  if (argc < 2)
  {
    fprintf (stderr, "USAGE: COMMCONV InFile [OutFile]\n");
    return (1);
  }
  if ((InFile = fopen (argv[1], "r")) == NULL)
  {
    fprintf (stderr, CannotOpen, argv[1]);
    return (3);
  }

  if (argc == 3)
  {
    if ((OutFile = fopen (argv[2], "w")) == NULL)
    {
      fprintf (stderr, CannotOpen, argv[2]);
      OutFile = stdout;  /* if can't open, output goes to stdout instead */
    }
  }

  while ((Char = fgetc (InFile)) != EOF)
  {
    fputc (Char, OutFile);

    if (Char == '\"')
      in_string = ! in_string;    /* toggle flag */

    if (in_string)                /* we are in a string now */
      continue;

    if (Char == '/')              /* slash */
    {
      Char = fgetc (InFile);      /* check next char */
      if (Char == '/')            /* is it start of C++ comment */
      {
        Char = '*';               /* change it to C comment */
        cpp_comment = 1;
      }
      else if (Char == '*')       /* is it start of C comment */
        c_comment = 1;

      fputc (Char, OutFile);

      if (c_comment || cpp_comment) /* inside C or C++ comment */
      {
        while ((Char = fgetc (InFile)) != '\n') /* rest of the line */
        {
          if (Char == '*' && c_comment)
          {
            int Ch = fgetc (InFile);         /* check next char */
            if (Ch == '/')                   /* is it end of C comment */
              c_comment = 0;
            ungetc (Ch, InFile);             /* put it back to stream */
          }
          fputc (Char, OutFile);
        }
        if (cpp_comment)
        {
          fputs (" *", OutFile);             /* put ending C comment mark */
          if (c_comment)
            fputc (' ', OutFile);
          fputc ('/', OutFile);
          cpp_comment = 0;
        }
        fputc ('\n', OutFile);
      }
    }
    else if (Char == '*' && c_comment)
    {
      Char = fgetc (InFile);
      if (Char == '/')                   /* is it end of C comment */
        c_comment = 0;
      fputc (Char, OutFile);
    }
  } /* while end */

  if (argc == 3)
    fclose (OutFile);
  fclose (InFile);

  return 0;
}
