/*
** rounding macros by Dave Knapp & Thad Smith
*/

/* round to integer */

#define iround(x) floor((x)+0.5)

/* round number n to d decimal points */

#define fround(n,d) (floor((n)*pow(10.,(d))+.5)/pow(10.,(d)))
