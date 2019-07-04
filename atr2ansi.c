/*
**  Form a command string for ANSI.SYS to set a given video attribute
**
**  Public domain demo by Bob Stout
*/

/* video attributes */

#define BLINKING 0x87
#define REVERSE 0x70
#define REVBLINK 0xf0
#define NORMAL 0x07
#define HIGHLITE 0x0f
#define HIGHBLINK 0x8f
#define BLINKBIT 0x80   /* OR in to cause blink */
#define HILTBIT 0x08    /* OR in to cause highlight */

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

/*
**  Example:
**   Video attribute of yellow text on blue background = BG_(BLUE)+YELLOW
*/

char *make_ansi(int vatr)
{
        void add_str(char *, char *);
        static char string[40];

        static char *fore[8] = {"30","34","32","36","31","35","33","37"};
        static char *back[8] = {"40","44","42","46","41","45","43","47"};

        strcpy(string, "\033[");
        if (vatr == 0x07)
                strcat(string, "0");
        else
        {
                if (vatr & 0x80)
                        add_str(string, "5");
                if (vatr & 0x08)
                        add_str(string, "1");
                add_str(string, fore[vatr & 0x07]);
                add_str(string, back[(vatr & 0x70) >> 4]);
        }
        strcat(string, "m");
        return string;
}

void add_str(char *string1, char *string2)
{
        char last_char;

        last_char = string1[strlen(string1) - 1];
        if (last_char != '[')
                strcat(string1, ";");
        strcat(string1, string2);
}
