/*
      This program is similar to a program of the same name found on UNIX.
      It prints the files named in the command tail with headings
      except as modified below.

      usage: pr [-i -ln -on -pname -tn -wn] file1[ file2 ... filen]
      where:            -i    = accept files from stdin
                  -ln   = set lines per page to n
                  -on   = set page offset to n
                  -pname      = output to file <name>
                  -tn   = set tabs to n cols
                  -wn   = set page width to n

      note: the expr 'PAGE(mesg)' found in col 1 will cause a formfeed
                  and the 'mesg' to be included in the title line on this and
                  each subsequent page until EOF or another PAGE.
*/

#include <stdio.h>

#define TAB_DEFAULT 4
#define PAGE_LENGTH 60
#define PAGE_OFFSET 0
#define PAGE_WIDTH      80
#define MAX_ARGS    70
#define MAX_FILES 64
#define PATH_LENGTH 63
#define PAGE(head)

#ifndef TRUE

#define TRUE 1
#define FALSE 0

#endif


int page_length = PAGE_LENGTH;
int page_offset = PAGE_OFFSET;
int page_width    = PAGE_WIDTH;

int tab_width = TAB_DEFAULT;

char *xargv[ MAX_ARGS ];
unsigned xargc;

char filenames [MAX_FILES] [PATH_LENGTH + 1];

char *print_name = "PRN:";

extern long atoi();

char title [80];
char date [20];
char time [20];
int ln, pn;

PAGE (MAIN)
main(argc, argv)  /* copy file to printer */
int  argc;
char *argv [];
{
      FILE *file, *lp;
      int fi = 0;
      int read_stdin = FALSE;
      int pn;
      char *cp;

      if (argc < 2) /* No args so tell 'em how it works */
      {
            fprintf(stderr,
            "usage:\n\npr %s %s\n\n",
            "[-i] [-lnn] [-onn] [-p<name>] [-tn] [-wnn]",
            "[file1[ file2 ... filen]]");
            fprintf(stderr,
            "where: i = read 'stdin' for filenames to print\n");
            fprintf(stderr,
            "       l = lines-per-page and nn <= 120\n");
            fprintf(stderr,
            "       o = page offset    and nn <= 120\n");
            fprintf(stderr,
            "       p = print redirection and\n");
            fprintf(stderr,
            "           <name> = pathname or devicename\n");
            fprintf(stderr,
            "       t = spaces-per-tab and n  <= 8\n");
            fprintf(stderr,
            "       w = page width     and nn <= 160\n\n");
            fprintf(stderr,
            "Notes: PAGE(<title text of any length>) in col 1 of text file\n");
            fprintf(stderr,
            "       and <title text...> the title you want.\n\n");
            fprintf(stderr,
            "       C pgms should include the following macro:\n\n");
            fprintf(stderr,
            "            #define PAGE(title)\n\n");
            fprintf(stderr,
            "       < and > not required and should not be used\n\n");
            exit(0);
      }

      xargc = xargs("pr", argc, argv, xargv, MAX_ARGS);
      
      for (pn = 0; pn < xargc; pn++)
      {
            if (*xargv[pn] == '-')
            {
                  cp = xargv[pn] + 1;
                  switch (tolower(*cp))
                  {
                  case 'i':/* wants help */
                        read_stdin = TRUE;
                        break;
                  case 'l':/* page length change */
                        page_length = (int) atoi(cp + 1);
                        if ((page_length <= 0) || (page_length > 120))
                              page_length = PAGE_LENGTH;
                        break;

                  case 'p':/* direct output to file */
                        print_name = cp + 1;
                        break;

                  case 't':/* tab width change */
                        tab_width = (int) atoi(cp + 1);
                        if ((tab_width <= 0) || (tab_width > 8))
                              tab_width = TAB_DEFAULT;
                        break;

                  case 'o':/* page offset change */
                        page_offset = (int) atoi(cp + 1);
                        if ((page_offset < 0) || (page_offset > 120))
                              page_offset = PAGE_OFFSET;
                        break;

                  case 'w':/* page width change */
                        page_width = (int) atoi(cp + 1);
                        if ((page_width <= 0) || (page_width > 160))
                              page_width = PAGE_WIDTH;
                        break;

                  default:
                        fprintf(stderr, "pr: Invalid option = %s\n",
                              xargv[pn]);
                  }
            }
            else  /* must be a path name */
            {
                  if (fi < MAX_FILES)
                        strcpy(filenames[fi++], xargv[pn]);
                  else
                  {
                        fprintf(stderr, "pr: "
                              "Exceeded maximum file capacity\n");
                        break;
                  }
            }
      }

      if ((lp = fopen(print_name, "w")) == 0)
      {
            fprintf(stderr, "pr: Unable to open %s as output\n", print_name);
            exit(1);
      }

      if (read_stdin)
      {
            for(;;)
            {
                  if (fi == MAX_FILES)
                  {
                        fputs("pr: Exceeded maximum file capacity\n",
                              stderr);
                        break;
                  }
                  cp = gets(filenames [fi], PATH_LENGTH);
                  if (!cp)
                        break;
                  else  fi++;
            }
      }
      /* now print each file */

      for (pn = 0; pn < fi; pn++)
            prt(filenames [pn], lp);  /* print the file */
}
PAGE (NEW PAGE)

new_page (fnp, lp)
char *fnp;
FILE *lp;
{
      if (ln < 3)
            return;
      ++pn;
      if (pn > 1)
            fputc('\f', lp);
      fprintf(lp, "%s    %s %s    PAGE %d:  %s\n\n",
                   fnp, date, time, pn, title);
      ln = 2;
}

PAGE (PRINT FILE)
prt (fnp, lp)
char fnp[];
FILE *lp;
{
      FILE *inp_file;
      int i, j, col;
      char line [256], *st, *et, *sp;

      inp_file = fopen(fnp, "r");
      if (!inp_file)
      {
            fprintf(stderr, "pr: unable to open %s\n", fnp);
            return;
      }
      else
            fprintf(stderr, "pr: printing %s\n", fnp);

      pn = 0;
      ln = 999;
      gdates(date);          /* get date */
      gtimes(time);          /* and time */
      *title = '\0';

      while (fgets(line, 256, inp_file))
      {
            if (strncmp(line, "PAGE", 4) == 0)
            {
                  if (st = index(line, '('))
                  {
                        et = index(line, ')');
                        strncpy(title, st + 1, (et) ? et - st - 1 : 160);
                  }
                  ln = 999;
            }

            if (ln > page_length)
                  new_page(fnp, lp);

            if (page_offset)
                  indent(lp);

            for (col = (page_offset) ? page_offset : 1, sp = &line[0];
                   *sp; sp++)
            {
                  switch (*sp)
                  {
                  case '\t':  /* tab character */
                        do
                        {
                              fputc(' ', lp);
                              col++;
                              if (col > page_width)
                              {
                                    fputc('\n', lp);
                                    col = (page_offset) ? page_offset : 1;
                                    ln++;
                                    if (ln > page_length)
                                          new_page(fnp, lp);
                                    if (page_offset)
                                          indent(lp);
                                    break;
                              }
                        } while ((col - 1) % tab_width);
                        break;

                  case '\f':  /* form feed character */
                        new_page(fnp, lp);
                        break;

                  default:
                        fputc(*sp, lp);
                        ++col;
                        if (col > page_width)
                        {
                              fputc('\n', lp);
                              col = (page_offset) ? page_offset - 1 : 0;
                              ln++;
                              if (ln > page_length)
                                    new_page(fnp, lp);
                              if (page_offset)
                                    indent(lp);
                        }
                  }
            } /* of line print (for) */
            ++ln;
      } /* of while not eof */
      fclose(inp_file);
      fputc(014, lp);
} /* of print */

indent(lp)
FILE *lp;
{
      int i;

      for(i = 1; i < page_offset; i++)
            fputc(' ', lp);
}
