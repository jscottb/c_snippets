/*
**  hugesort.c -- huge qsort() -- public domain by Raymond Gardner 6/92
**  tested with Borland C++ 3.0 (C mode)
*/

static void swap(char huge *a, char huge *b, unsigned n)
{
      char tmp;

      do
      {
            tmp = *a; *a++ = *b; *b++ = tmp;
      } while ( --n );
}
void hugesort(void huge *basep,
              unsigned   nel,
              unsigned   width,
              int      (*comp)(void huge *, void huge *))
{
      char huge *i, huge *j;
      unsigned int lnel, rnel;
      char huge *base = (char huge *)basep;

      while (nel > 1)
      {
            swap(base, base + (long)width * (nel / 2), width);
            for (i = base, j = base + (long)width * nel; ; )
            {
                  do
                        j -= width;
                  while ( (*comp)(j, base) > 0 );
                  do
                        i += width;
                  while ( i < j && (*comp)(i, base) < 0 );
                  if (i >= j)
                        break;
                  swap(i, j, width);
            }
            swap(j, base, width);
            lnel = (unsigned)((long)(j - base) / width);
            rnel = nel - lnel - 1;
            j += width;
            if (lnel < rnel)
            {
                  hugesort(base, lnel, width, comp);
                  base = j;
                  nel = rnel;
            }
            else
            {
                  hugesort(j, rnel, width, comp);
                  nel = lnel;
            }
      }
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <alloc.h>

#define PADSIZE 300

typedef struct x {
    int key;
    char pad[PADSIZE];
    } X;

int cmpv(void huge *a, void huge *b) /* (note void huge *) passed here */
{
      return ((X huge *)a)->key < ((X huge *)b)->key ? -1 :
            ((X huge *)a)->key > ((X huge *)b)->key ? 1 : 0;
}

int main(int argc, char **argv)
{
      X huge *v;
      int n;
      int i, j;

      n = 300;                            /* default element count */
      if (argc > 1)
            n = atoi(argv[1]);
      printf("test with %d elements\n", n);
      v = farmalloc(sizeof(X) * (long)n);
      assert(v);                          /* be sure we got memory */
      for (i = 0; i < n; ++i)             /* random init */
      {
            v[i].key = rand();
            for (j = 0; j < PADSIZE; ++j)
                  v[i].pad[j] = rand();
      }
      for (i = 0; i < n; ++i)             /* display before */
            printf(" %d", v[i].key);
      printf("\n");
      hugesort(v, n, sizeof(X), cmpv);    /* sort it */
      for ( i = 0; i < n; ++i )           /* display after */
            printf(" %d", v[i].key);
      printf("\n");
      return 0;
}

#endif
