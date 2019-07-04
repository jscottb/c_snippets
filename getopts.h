/*
**  GETOPTS.H
**
**  public domain by Bob Stout
*/

#undef ERROR
#undef FALSE
#undef TRUE

typedef enum {ERROR = -1,FALSE, TRUE} Boolean_T;

typedef enum {
      Boolean_Tag,
      Word_Tag,
      DWord_Tag,
      Double_Tag,
      String_Tag
      } TAG_TYPE;

struct Option_Tag {
      int         letter;                 /* Option switch        */
      TAG_TYPE    type;                   /* Type of option       */
      void       *buf;                    /* Storage location     */
};

extern struct Option_Tag options[];
extern int    xargc;
extern char  *xargv[];

int getopts(int, char *[]);
