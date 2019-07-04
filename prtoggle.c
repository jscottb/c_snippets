/*
**  prtoggle()
**
**  Tee's all standard output to the printer.
**
**  Parameters: None
**
**  Returns:  0 if operation was successful.
**           -1 if stdout or stdin is redirected.
**
**  Side effects: Flushes the keyboard buffer
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>

#if !defined(__ZTC__) && !defined(__TURBOC__)
 #define MK_FP(seg,offset) \
        ((void far *)(((unsigned long)(seg)<<16) | (unsigned)(offset)))
 #define peek(s,o) (*((unsigned far *)(MK_FP(s,o))))
 #define poke(s,o,w) (*((unsigned far *)(MK_FP(s,o)))=(w))
#endif

#define SUCCESS 0
#define ERROR -1

static unsigned head, tail, start, end;
static int idx = 0;
static unsigned keystack[16][2];

int ungetkey(unsigned key)
{
        int count;

#ifdef __ZTC__
        peek(0x40, 0x1a, &head, sizeof(unsigned));
        peek(0x40, 0x1c, &tail, sizeof(unsigned));
#else
        head = peek(0x40, 0x1a);
        tail = peek(0x40, 0x1c);
#endif
        count = tail - head;
        if (0 > count)
                count += (16 * sizeof(unsigned));
        count >>= 1;

        if (15 > count)
        {
#ifdef __ZTC__
                peek(0x40, tail, &keystack[idx][0], sizeof(unsigned));
#else
                keystack[idx][0] = peek(0x40, tail);
#endif
                keystack[idx][1] = tail;
#ifdef __ZTC__
                poke(0x40, tail, &key, sizeof(unsigned));
#else
                poke(0x40, tail, key);
#endif
                tail += sizeof(unsigned);
                if (0x3e <= tail)
                        tail = 0x1e;
#ifdef __ZTC__
                poke(0x40, 0x1c, &tail, sizeof(unsigned));
#else
                poke(0x40, 0x1c, tail);
#endif
                return key;
        }
        return EOF;
}

int prtoggle(void)
{
      if (!isatty(fileno(stdin)) || !isatty(fileno(stdout)))
            return -1;
      while (kbhit())           /* Flush the keyboard buffer            */
            getch();
      ungetkey('P' - 64);       /* Stuff a Ctrl-P into the buffer       */
      system("");               /* Let COMMAND.COM do the work          */
      return 0;
}
