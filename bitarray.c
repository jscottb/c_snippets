char set[(BITCOUNT + 7) / 8];

int getbit(char *set, int number)
{
        set += number / 8;
        return (*set & (1 << (number % 8))) != 0;       /* 0 or 1       */
}

int setbit(char *set, int number, int value)
{
        set += number / 8;
        if (value)
                *set |= 1 << (number % 8);              /* set bit      */
        else    *set &= ~(1 << (number % 8));           /* clear bit    */
}
