/*
**  Tasker.H
**
**  public domain by David Gibbs
*/

#ifndef DG_TASKER
#define DG_TASKER

struct ts_os_ver {
      int maj;
      int min;
};

#define TOT_OS  5

#define DOS     0
#define OS2     1
#define DV      2
#define WINS    3
#define WIN3    4

                        /*   76543210  */
#define is_DOS  0x01    /* b'00000001' */
#define is_OS2  0x02    /* b'00000010' */
#define is_DV   0x04    /* b'00000100' */
#define is_WINS 0x08    /* b'00001000' */
#define is_WIN3 0x10    /* b'00010000' */


extern int t_os_type;
extern int t_os;

extern const char *t_os_name[TOT_OS];

extern struct ts_os_ver t_os_ver[TOT_OS];


/* Function prototypes */

int get_os();
void t_slice();

#endif /* DG_TASKER */
