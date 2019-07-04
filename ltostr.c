/*
**  LTOSTR.C -- routine and example program to convert a long int to
**  the specified numeric base, from 2 to 36.
**
**  Written by Thad Smith III, Boulder, CO. USA  9/06/91 
**  and contributed to the Public Domain.
*/

#include <stdlib.h>

char *                  /* addr of terminating null */
ltostr (
    char *str,          /* output string */
    long val,           /* value to be converted */
    unsigned base)      /* conversion base       */
{
    ldiv_t r;           /* result of val / base */

    if (base > 36)      /* no conversion if wrong base */
    {
        str = '\0';
        return str;
    }
    if (val < 0)    *str++ = '-';
    r = ldiv (labs(val), base);

    /* output digits of val/base first */

    if (r.quot > 0)  str = ltostr (str, r.quot, base);

    /* output last digit */

    *str++ = "0123456789abcdefghijklmnopqrstuvwxyz"[(int)r.rem];
    *str   = '\0';
    return str;
}

#include <stdio.h>
main()
{
    char buf[100], line[100], *tail;
    long v;
    int inbase, outbase;

    for (;;)
    {
        printf ("inbase, value, outbase? ");
        fgets (line, sizeof line, stdin);
        sscanf (line, " %d%*[, ]%[^, ]%*[, ]%d", &inbase, buf, &outbase);
        if (inbase == 0)
            break;                              /* exit if first number 0 */
        v = strtol (buf, &tail, inbase);
        ltostr (buf, v, outbase);
        printf ("=%ld (10) = %s (%d).\n", v, buf, outbase);
    };
    return 0;
}
