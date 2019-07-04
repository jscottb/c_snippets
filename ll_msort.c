/*
** Here's an example of how to sort a singly-linked list.  I think it
** can be modified to sort a doubly-linked list, but it would get a bit
** more complicated.  Note that this is a recursive method, but the
** recursion depth is limited to be proportional to the base 2 log of
** the length of the list, so it won't "run away" and blow the stack.
**
**  10/21/93 rdg  Fixed bug -- function was okay, but called incorrectly.
*/

/* linked list sort -- public domain by Ray Gardner  5/90 */

#include <stdio.h>              /* for NULL definition */
#include <string.h>

typedef struct list_struct {
   struct list_struct *next;
   char *key;
   /* other stuff */
   } list;

/* returns < 0 if *p sorts lower than *q */
int keycmp (list *p, list *q)
{
      return strcmp(p->key, q->key);
}

/* merge 2 lists under dummy head item */
list *lmerge (list *p, list *q)
{
      list *r, head;

      for ( r = &head; p && q; )
      {
            if ( keycmp(p, q) < 0 )
            {
                  r = r->next = p;
                  p = p->next;
            }
            else
            {
                  r = r->next = q;
                  q = q->next;
            }
      }
      r->next = (p ? p : q);
      return head.next;
}

/* split list into 2 parts, sort each recursively, merge */
list *lsort (list *p)
{
      list *q, *r;

      if ( p )
      {
            q = p;
            for ( r = q->next; r && (r = r->next) != NULL; r = r->next )
                  q = q->next;
            r = q->next;
            q->next = NULL;
            if ( r )
                  p = lmerge(lsort(r), lsort(p));
      }
      return p;
}

main (void)
{
      list *listp;                 /* pointer to start of list */

      /* first build unsorted list, then */

      listp = lsort(listp);                                 /* rdg 10/93 */

      return 0;
}
