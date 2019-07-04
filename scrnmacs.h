/*
**  Macros for managing direct video writes by Jerry Houston
**
**  prototypes for SCROLL.C and VIDPORT.C functions added by Bob Stout
*/

#if defined(__TURBOC__)
 #define FAR far
#else
 #define FAR _far
#endif
 
#ifndef MK_FP
 #define MK_FP(seg,off) ((void far *)(((long)(seg) << 16)|(unsigned)(off)))
#endif

/*
**  Text screen scrolling function from SCROLL.C in SNIPPETS
*/
 
#define SCROLL_UP 0
#define SCROLL_DN 1

void scroll(int direction,
            int num_lines,
            int vattrib,
            int ulrow,
            int ulcomumn,
            int lrrow,
            int lrcolumn);

/*
**  Functions in VIDPORT.C in SNIPPETS
*/
 
void GotoXY(int col, int row);
void ClrScrn(int vattrib);
void GetCurPos(int *col, int *row);
int  GetCurAtr(void);
void ClrEol(void);
void ClrEop(void);
void Repaint(int vattrib);

#if !defined(COLORMODE)
 #define COLORMODE  ((*(char FAR *)0x0449) != 7)
 #define EXT_KBD    (*(char FAR *)0x0496 & 16)
 #define VIDPAGE    (*((unsigned char far *)0x0462))
 #define ROWSIZE    (*(int FAR *)0x044A)
 #define SCANLINES  ((int)*(char FAR*)0x0461)
 #define SCRBUFF    ((unsigned FAR *)((COLORMODE)?0xB8000000:0xB0000000))
 #define SCREENSEG  ((unsigned)((COLORMODE)?0xB800:0xB000))
 #define SCREENSIZE ((*(int FAR *)0x044C) >> 1)
 #define SCREENCOLS (*(int FAR *)0x044A)
 #define SCREENROWS ((*(char FAR *)0x0484)?1+(*(char FAR *)0x0484):25)
#endif

/*
     COLORMODE  = true/false, are we using color?
     EXT_KBD    = true/false, extended keyboard in use?
     VIDPAGE    = current video page in use
     SCANLINES  = number of scan lines in a character.
     SCRBUFF    = returns B800:0000 if using color, B000:0000 if mono.
     SCREENSEG  = when you just need the segment portion.
     SCREENSIZE = number of (2-byte) cells required to save screen.
     SCREENCOLS = number of columns, often 80.
     SCREENROWS = number of rows, usually defaults to 25.
*/

/*
** colors -- Use as is for foreground colors
**           For background, shift left by 4 and OR with
**           foreground and possible video attributes
*/

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define WHITE 7
#define GRAY 8
#define LTBLUE 9
#define LTGREEN 10
#define LTCYAN 11
#define LTRED 12
#define LTMAGENTA 13
#define YELLOW 14
#define HIWHITE 15    /* hi-intensity white */

#define BG_(a) (((a) & 0x7f) << 4)
