/*
**  ext_getch() header file.
**
**  ext_getch() returns:
**
**           0->255     Normal key
**           256->511   Numeric pad key or Function key
**           512->767   Cursor pad key or Numeric pad
**                      "duplicate" key (Enter, /, *, -, +)
*/
 
int ext_getch(void);
 
#define Key_F1          0x13b       /* Function keys              */
#define Key_F2          0x13c
#define Key_F3          0x13d
#define Key_F4          0x13e
#define Key_F5          0x13f
#define Key_F6          0x140
#define Key_F7          0x141
#define Key_F8          0x142
#define Key_F9          0x143
#define Key_F10         0x144
#define Key_F11         0x185
#define Key_F12         0x186
#define Key_CF1         0x15e       /* Ctrl-Function keys         */
#define Key_CF2         0x15f
#define Key_CF3         0x160
#define Key_CF4         0x161
#define Key_CF5         0x162
#define Key_CF6         0x163
#define Key_CF7         0x164
#define Key_CF8         0x165
#define Key_CF9         0x166
#define Key_CF10        0x167
#define Key_CF11        0x189
#define Key_CF12        0x18a
#define Key_SF1         0x154       /* Shift-Function keys        */
#define Key_SF2         0x155
#define Key_SF3         0x156
#define Key_SF4         0x157
#define Key_SF5         0x158
#define Key_SF6         0x159
#define Key_SF7         0x15a
#define Key_SF8         0x15b
#define Key_SF9         0x15c
#define Key_SF10        0x15d
#define Key_SF11        0x187
#define Key_SF12        0x188
#define Key_AF1         0x168       /* Alt-Function keys          */
#define Key_AF2         0x169
#define Key_AF3         0x16a
#define Key_AF4         0x16b
#define Key_AF5         0x16c
#define Key_AF6         0x16d
#define Key_AF7         0x16e
#define Key_AF8         0x16f
#define Key_AF9         0x170
#define Key_AF10        0x171
#define Key_AF11        0x18b
#define Key_AF12        0x18c
#define Key_INS         0x152       /* Numeric pad keys           */
#define Key_DEL         0x153
#define Key_HOME        0x147
#define Key_END         0x14f
#define Key_PGUP        0x149
#define Key_PGDN        0x151
#define Key_UPARROW     0x148
#define Key_DNARROW     0x150
#define Key_LTARROW     0x14b
#define Key_RARROW      0x14d
#define Key_PADMIDDLE   0x14c
#define Key_PADEQ       0x3d
#define Key_PADPLUS     0x22b
#define Key_PADMINUS    0x22d
#define Key_PADASTERISK 0x22a
#define Key_PADSLASH    0x22f
#define Key_C1          0x175       /* Ctrl-Numeric pad keys      */
#define Key_C2          0x191
#define Key_C3          0x176
#define Key_C4          0x173
#define Key_C5          0x18f
#define Key_C6          0x174
#define Key_C7          0x177
#define Key_C8          0x18d
#define Key_C9          0x184
#define Key_PINS        0x252       /* Cursor pad keys            */
#define Key_PDEL        0x253
#define Key_PHOME       0x247
#define Key_PEND        0x24f
#define Key_PPGUP       0x249
#define Key_PPGDN       0x251
#define Key_PUPARROW    0x248
#define Key_PDNARROW    0x250
#define Key_PLTARROW    0x24b
#define Key_PRTARROW    0x24d
 
#define Key_ESC         0x1b
