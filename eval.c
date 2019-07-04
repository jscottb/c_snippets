/*
**  EVAL.C - A simple mathematical expression evaluator in C
**
**  operators supported: (
**                       )
**                       +
**                       -
**                       *
**                       /
**                       ^
**
**  limitations: 1 - No precedence rules are implemented.
**               2 - Numbers can be negated (e.g. "-13"), but not
**                   expressions (e.g. "-(13)").
**
**  Original Copyright 1991 by Bob Stout as part of
**  the MicroFirm Function Library (MFL)
**
**  This subset* version is hereby donated to the public domain.
**
**  *(The MFL version adds 150 lines of code, 5 level precedence,
**    logarithmic and transcendental operators, pi as a constant,
**    named variables, and fully understands negation.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NUL '\0'

typedef enum {R_ERROR = -2 /* range */, ERROR /* syntax */, SUCCESS} STATUS;

static char   delims[]   = "+-*/^)(";           /* Tokens               */
static char   op_stack[256];                    /* Operator stack       */
static double arg_stack[256];                   /* Argument stack       */
static char   token[256];                       /* Token buffer         */
static int    op_sptr,                          /* op_stack pointer     */
              arg_sptr,                         /* arg_stack pointer    */
              parens,                           /* Nesting level        */
              state = 0;                        /* 0 = Awaiting expression
                                                   1 = Awaiting operator
                                                */

int evaluate(char *, double *);

static int        do_op(void);
static int        do_paren(void);
static void       push_op(char);
static void       push_arg(double);
static STATUS     pop_arg(double *);
static STATUS     pop_op(int *);
static char      *getexp(char *);
static char      *getop(char *);
static void       pack(char *);

#ifdef TEST

void main(int argc, char *argv[])
{
      double val;

      printf("evaluate(%s) ", argv[1]);
      printf("returned %d\n", evaluate(argv[1], &val));
      printf("val = %f\n", val);
}

#endif

/*
**  Evaluate a mathematical expression
*/

int evaluate(char *line, double *val)
{
      double arg;
      char *ptr = line, *str, *endptr;
      int ercode;

      pack(line);

      while (*ptr)
      {
            switch (state)
            {
            case 0:
                  if (NULL != (str = getexp(ptr)))
                  {
                        if ('(' == *str)
                        {
                              push_op(*str);
                              ptr += strlen(str);
                              break;
                        }

                        if (0.0 == (arg = strtod(str, &endptr)) &&
                              NULL == strchr(str, '0'))
                        {
                              return ERROR;
                        }
                        push_arg(arg);
                        ptr += strlen(str);
                  }
                  else  return ERROR;

                  state = 1;
                  break;

            case 1:
                  if (NULL == (str = getop(ptr)))
                        return ERROR;

                  if (strchr(delims, *str))
                  {
                        if (')' == *str)
                        {
                              if (SUCCESS > (ercode = do_paren()))
                                    return ercode;
                        }
                        else
                        {
                              push_op(*str);
                              state = 0;
                        }

                        ptr += strlen(str);
                  }
                  else  return ERROR;

                  break;
            }
      }

      while (1 < arg_sptr)
      {
            if (SUCCESS > (ercode = do_op()))
                  return ercode;
      }
      if (!op_sptr)
            return pop_arg(val);
      else  return ERROR;
}

/*
**  Evaluate stacked arguments and operands
*/

static int do_op(void)
{
      double arg1, arg2;
      int op;

      if (ERROR == pop_op(&op))
            return ERROR;

      pop_arg(&arg1);
      pop_arg(&arg2);

      switch (op)
      {
      case '+':
            push_arg(arg2 + arg1);
            break;

      case '-':
            push_arg(arg2 - arg1);
            break;

      case '*':
            push_arg(arg2 * arg1);
            break;

      case '/':
            if (0.0 == arg1)
                  return R_ERROR;
            push_arg(arg2 / arg1);
            break;

      case '^':
            if (0.0 > arg2)
                  return R_ERROR;
            push_arg(pow(arg2, arg1));
            break;

      case '(':
            arg_sptr += 2;
            break;

      default:
            return ERROR;
      }
      if (1 > arg_sptr)
            return ERROR;
      else  return op;
}

/*
**  Evaluate one level
*/

static int do_paren(void)
{
      int op;

      if (1 > parens--)
            return ERROR;
      do
      {
            if (SUCCESS > (op = do_op()))
                  break;
      } while ('('!= op);
      return op;
}

/*
**  Stack operations
*/

static void push_op(char op)
{
      if ('(' == op)
            ++parens;
      op_stack[op_sptr++] = op;
}

static void push_arg(double arg)
{
      arg_stack[arg_sptr++] = arg;
}

static STATUS pop_arg(double *arg)
{
      *arg = arg_stack[--arg_sptr];
      if (0 > arg_sptr)
            return ERROR;
      else  return SUCCESS;
}

static STATUS pop_op(int *op)
{
      if (!op_sptr)
            return ERROR;
      *op = op_stack[--op_sptr];
      return SUCCESS;
}

/*
**  Get an expression
*/

static char *getexp(char *str)
{
      char *ptr = str, *tptr = token;

      while (*ptr)
      {
            if (strchr(delims, *ptr))
            {
                  if ('-' == *ptr)
                  {
                        if (str != ptr && 'E' != ptr[-1])
                              break;
                  }

                  else if (str == ptr)
                        return getop(str);

                  else if ('E' == *ptr)
                  {
                        if (!isdigit(ptr[1]) && '-' != ptr[1])
                              return NULL;
                  }
                  else break;
            }

            *tptr++ = *ptr++;
      }
      *tptr = NUL;

      return token;
}

/*
**  Get an operator
*/

static char *getop(char *str)
{
      *token = *str;
      token[1] = NUL;
      return token;
}

/*
**  Remove whitespace & capitalize
*/

static void pack(char *str)
{
      char *ptr = str, *p;

      strupr(str);

      for ( ; *ptr; ++ptr)
      {
            p = ptr;
            while (*p && isspace(*p))
                  ++p;
            if (ptr != p)
                  strcpy(ptr, p);
      }
}
