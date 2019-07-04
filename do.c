/*
**  DO.C - a simple facility for specifying multiple commands
*/

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
      if (2 > argc)
      {
            puts("Usage: DO \"DOS command 1\" \"DOS command 2\" ...");
            return;
      }
      while (--argc)
            system(*++argv);
}
