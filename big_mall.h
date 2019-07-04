/*
** void _far *BigMalloc(unsigned long num_elem, size_t size_elem)
*/

#ifdef MSDOS
 #if defined(__TURBOC__) || defined(__ZTC__)
  #ifdef __TURBOC__
   #define _far far
  #endif
  #define BigMalloc(i,n) (void _far *)farmalloc(i*n)
 #else                                          /* MSC, Watcom  */
  #define BigMalloc(i,n) (void _far *)halloc(i,n)
#else
 #define BigMalloc(i,n) malloc(i*n)
#endif 
