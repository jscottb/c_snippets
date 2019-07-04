/*
**  By: Jim Nutt
*/

#ifndef VIO_H
#define VIO_H

#if __cplusplus
extern "C" {
#endif

#if defined(__TURBOC__)
 #define _far far
 #define _pascal pascal
#endif

/* initialization and termination functions */

int  _far VIOopen(void);
void _far VIOclose(void);

/* scrolling functions */

void _far VIOscrollright(int x1, int y1, int x2, int y2, int count);
void _far VIOscrollleft(int x1, int y1, int x2, int y2, int count);
void _far VIOscrollup(int x1, int y1, int x2, int y2, int count);
void _far VIOscrolldown(int x1, int y1, int x2, int y2, int count);

/* screen clear */

void _far VIOclear(int x1, int y1, int x2, int y2);

/* write to screen */

void _far VIOputc(const char c);
void _far VIOputs(const char far * s);
void _far VIOputr(int x, int y, int w, int h, int _far * b);

/* read from screen */

int _far VIOgetca(const int x, const int y);
int _far * _far VIOgetra(int x1, int y1, int x2, int y2, int _far * b);

/* set colors */

void _far VIOsetfore(const int c);
void _far VIOsetback(const int c);

/* get current color settings */

int  _far VIOgetfore(void);
int  _far VIOgetback(void);

/* set the write cursor */

void _far VIOgotoxy(int x, int y);

/* update the screen and visible cursor */

void _far VIOupdate();

/* get the current write cursor position */

int  _far VIOwherex(void);
int  _far VIOwherey(void);

/* get screen information */

unsigned int  _far VIOsegment(void);

int  _far VIOcolumns(void);
int  _far VIOrows(void);
int  _far VIOmode(void);
int  _far VIOheight(void);

/* set segment information */

void _far VIOsetSegment(unsigned int s);
void _far VIOsetRows(int r);
void _far VIOsetCols(int c);

/* get BIOS cursor location */

void _far VIOcursor(int _far * x, int _far * y, int _far * shape);

#if __cplusplus
} ;
#endif

#endif
