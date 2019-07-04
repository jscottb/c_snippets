static volatile unsigned char far *keyflags = (char far *)0x00400017;

void setcaps(void)
{
        *keyflags |= 0x40;
}

void clrcaps(void)
{
        *keyflags &= ~0x40;
}

void setnumlock(void)
{
        *keyflags |= 0x20;
}

void clrnumlock(void)
{
        *keyflags &= ~0x20;
}
