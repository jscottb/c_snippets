/*
**  BASIC-like string operations
**
**  public domain by Bob Stout
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

static int stralloc_ptr;
static char *strings[8];
static int str_tag[8];

/*
**  stralloc() is the key function in this package, maintaining a pool of
**  reusable strings.
*/

char *stralloc(size_t length)
{
        register int i;

        i = stralloc_ptr++;
        if ((!strings[i]) || (length > strlen(strings[i])))
        {
                assert(strings[i] = (char *)realloc(strings[i], length));
                str_tag[i] = -1;
        }
        else    str_tag[i] = 0;
        stralloc_ptr &= 7;
        return (strings[i]);
        /* Maintains 8 strings in a circular buffer */
}

/*
**  free the string pool.
*/

void str_free(char *string)
{
        register int i;

        for (i = 0; i < 8; ++i)
        {
                if (strings[i] == string)
                {
                        if (str_tag[i])
                                free(strings[i]);
                        return;
                }
        }
}

/*
**  return the leftmost N characters from a string
*/

char *left(char *string, size_t N)
{
        char *buf;
        size_t strlength = strlen(string);

	if (N > strlength)
                N = strlength;
        buf = stralloc(N + 1);
        memcpy(buf, string, N);
        buf[N] = '\0';
        return buf;
}

/*
**  return the rightmost N characters from a string
*/

char *right(char *string, size_t N)
{
        char *buf;
        size_t strlength = strlen(string);

	if (N > strlength)
                N = strlength;
        buf = stralloc(N + 1);
        strcpy(buf, &string[strlength-N]);
        return buf;
}

/*
**  return a substring, N characters long beginning at position M
*/

char *mid(char *string, size_t M, size_t N)
{
        char *buf;
        size_t strlength = strlen(string);

	if (M > strlength)
                return NULL;
        if (N > (strlength - M))
                N = strlength - M;
        buf = stralloc(N + 1);
        memcpy(buf, &string[M-1], N);
        buf[N] = '\0';
        return buf;
}

/*
**  string concatenation function, equivalent to A$=B$+C$+...
*/

char *string_add(char *string, ...)
{
        va_list arg_ptr;
        char *temp1, *temp2, *buf;

        va_start(arg_ptr, string);
        temp1 = string;
        do
        {
                if(NULL == (temp2 = va_arg(arg_ptr, char *)))
                        break;
                buf = stralloc(strlen(temp1) + strlen(temp2) + 1);
                temp1 = strcat(strcpy(buf, temp1), temp2);
        } while (NULL != temp2);
        return temp1;
}

#ifdef TEST

/*
**  Demo main()
*/

void main(void)
{
        char *x = "European", *y = "Hardware", *z = "Skaters";

        z = string_add(left(x, 2), right(y, 2), mid(z, 2, 2), "!", NULL);
        puts(z);
}

#endif /* TEST */
