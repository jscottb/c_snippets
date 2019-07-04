/*
**  JOYSTICK.H
**
**  Joystick support functions
**
**  Public domain demo by Bob Stout
*/

typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

#define BOOL(x) (!(!(x)))
#define SUCCESS 0

struct joystick {
        LOGICAL switch_0;
        LOGICAL switch_1;
        LOGICAL switch_2;
        LOGICAL switch_3;

        int     pos_Ax;
        int     pos_Ay;
        int     pos_Bx;
        int     pos_By;
};

LOGICAL read_joystick(void);

/*
**  JOYSTICK.C
**
**  Joystick support functions
**
**  Public domain demo by Bob Stout
*/

#include <dos.h>
#include "joystick.h"

struct joystick JoyStick;

/*
**  read_joystick()
**
**  returns SUCCESS or ERROR
**
**  fills in global JoyStick structure
*/

LOGICAL read_joystick(void)
{
        union REGS regs;

        regs.h.ah = 0x84;                       /* Read the switches    */
        regs.x.dx = 0;
        int86(0x15, &regs, &regs);
        if (regs.x.cflag)
                return ERROR;
        JoyStick.switch_0 = BOOL(regs.h.al & 0x10);
        JoyStick.switch_1 = BOOL(regs.h.al & 0x20);
        JoyStick.switch_2 = BOOL(regs.h.al & 0x40);
        JoyStick.switch_3 = BOOL(regs.h.al & 0x80);

        regs.h.ah = 0x84;                       /* Read positions       */
        regs.x.dx = 1;
        int86(0x15, &regs, &regs);
        if (regs.x.cflag)
                return ERROR;
        JoyStick.pos_Ax = regs.x.ax;
        JoyStick.pos_Ay = regs.x.bx;
        JoyStick.pos_Bx = regs.x.cx;
        JoyStick.pos_By = regs.x.dx;

        return SUCCESS;
}
