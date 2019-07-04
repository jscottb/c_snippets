/*
** from Bob Jarvis
*/

#include <stdio.h>
#include <ctype.h>

char *soundex(char *instr, char *outstr)
{                   /* ABCDEFGHIJKLMNOPQRSTUVWXYZ */
        char *table = "01230120022455012623010202";
        int count = 0;

        while(!isalpha(instr[0]) && instr[0])
                ++instr;

        if(!instr[0])     /* Hey!  Where'd the string go? */
                return(NULL);

        if(toupper(instr[0]) == 'P' && toupper(instr[1]) == 'H')
        {
                instr[0] = 'F';
                instr[1] = 'A';
        }

        *outstr++ = (char)toupper(*instr++);

        while(*instr && count < 5)
        {
                if(isalpha(*instr) && *instr != *(instr-1))
                {
                        *outstr = table[toupper(instr[0]) - 'A'];
                        if(*outstr != '0')
                        {
                                ++outstr;
                                ++count;
                        }
                }
                ++instr;
        }

        *outstr = '\0';
        return(outstr);
}
