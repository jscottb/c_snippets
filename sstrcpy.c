#include <string.h>

char *sstrcpy(char *to, char *from)
{
    memmove(to, from, 1+strlen(from));
    return to;
}

char *sstrcat(char *to, char *from)
{
    sstrcpy(to + strlen(to), from);
    return to;
}
