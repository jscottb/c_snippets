/*
**  SETENVAR.C - Program which sets the DOS master environment upon exit
**
**  Original Copyright 1988-1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset version is functionally identical to the
**  version originally published by the author in Tech Specialist
**  magazine and is hereby donated to the public domain.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

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

/*
**  ungetkey()
**
**  Stuffs characters into the keyboard buffer.
**
**  Parameters: 1 - Extended character to stuff
**
**  Returns: SUCCESS or EOF
**
**  Note: This function assumes that the keyboard buffer is in
**        the normal (for IBM) location of 40:1E.
**
*/

int ungetkey(unsigned key)
{
        int count;

#ifdef __ZTC__
        peek(0x40, 0x1a, &head, sizeof(unsigned));
        peek(0x40, 0x1c, &tail, sizeof(unsigned));
        peek(0x40, 0x80, &start, sizeof(unsigned));
        peek(0x40, 0x82, &end, sizeof(unsigned));
#else
        head  = peek(0x40, 0x1a);
        tail  = peek(0x40, 0x1c);
        start = peek(0x40, 0x80);
        end   = peek(0x40, 0x82);
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
                if (end <= tail)
                        tail = start;
#ifdef __ZTC__
                poke(0x40, 0x1c, &tail, sizeof(unsigned));
#else
                poke(0x40, 0x1c, tail);
#endif
                return key;
        }
        return EOF;
}

/*
**  KB_stuff()
**
**  Stuffs strings into the keyboard buffer.
**
**  Parameters: 1 - String to stuff
**
**  Returns: SUCCESS if successful
**           ERROR   in case of error, plus beyboard buffer is
**                   restored
**
**  Note: This function assumes that the keyboard buffer is in
**        the normal (for IBM) location of 40:1E.
*/

int KB_stuff(char *str)
{
        int ercode = SUCCESS;

        idx = 0;
        while (*str)
        {
                if (EOF == ungetkey((unsigned)(*str++)))
                {
                        while (0 <= --idx)
                        {
                                tail = keystack[idx][1];
#ifdef __ZTC__
                                poke(0x40, tail, &keystack[idx][0],
                                        sizeof(unsigned));
#else
                                poke(0x40, tail, keystack[idx][0]);
#endif
                        }
#ifdef __ZTC__
                        poke(0x40, 0x1c, &tail, sizeof(unsigned));
#else
                        poke(0x40, 0x1c, tail);
#endif
                        ercode = ERROR;
                        break;
                }
                else    ++idx;
        }
        idx = 0;
        return ercode;
}

void main(int argc, char *argv[])
{
        FILE *bfile;

        if (3 > argc)
        {
                puts("\aUsage: SETENVAR envar datum");
                abort();
        }
        bfile = fopen("$TMP$.BAT", "w");
        fprintf(bfile, "SET %s=%s\ndel $tmp$.bat\x1a", argv[1], argv[2]);
        fclose(bfile);
        while (kbhit())
                getch();
        KB_stuff("$tmp$\r");
}
