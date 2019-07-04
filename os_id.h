/*
**  OS_ID.H
**
**  Based upon a public domain work by David Gibbs
*/

#ifndef OS_ID_H
#define OS_ID_H

struct i_os_ver
{
  int maj;
  int min;
};

#define DOS     0
#define OS2     1
#define DV      2
#define WINS    3
#define WIN3    4
#define TOT_OS  5

                        /*   76543210  */
#define is_DOS  0x01    /* b'00000001' */
#define is_OS2  0x02    /* b'00000010' */
#define is_DV   0x04    /* b'00000100' */
#define is_WINS 0x08    /* b'00001000' */
#define is_WIN3 0x10    /* b'00010000' */

#ifndef OS_ID_MAIN
  extern int id_os_type;
  extern int id_os;
  extern const char *id_os_name[TOT_OS];
  extern struct id_os_ver i_os_ver[TOT_OS];
#endif

/* Function prototypes */
int get_os();

#endif /* OS_ID_H */

