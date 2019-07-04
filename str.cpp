//
// Implements simple string class 'str'
//

# include "str.h"
# include <string.h>
# include <memory.h>
# if defined( _MSC_VER )
# pragma warning(disable:4505)
# endif

# define STDLEN 32

extern "C" void * malloc (unsigned sz);
extern "C" void free (void * ptr);

# if defined( PLACEMENT_NEW_BUG )

inline void *
operator new (unsigned sz, short allocsz)
{
    return malloc (sz + allocsz);
}

# else

void *
refstr::operator new (unsigned sz, short allocsz)
{
    return malloc (sz + allocsz);
}

# endif

void
str::_strinit (char const * s, short len, short siz)
{
    if (len < 0)
        len = (short) ((s) ? strlen (s) : 0);
    if (siz < 0)
        siz = STDLEN;
    if (siz < len + 1)
        siz = short(len + 1);
    strdata = new(siz) refstr(len, siz);
    if (s && len)
        memcpy (c_ptr(), s, len);
}

        // Called whenever string is to be modified or grown
int
str::_chksize (short sz)
{
    refstr * old = 0;
    if (strdata->_refs > 1) // Need to dup memory
        --strdata->_refs;   // Dec existing string reference
    else if (sz >= size())
        old = strdata;
    else
        return 0;
    _strinit (c_ptr(), length(), sz);
    delete old;
    return 1;
}

str &
str::operator= (str const & s)
{
    if (&s != this)
    {
        if (!--strdata->_refs)
            delete strdata;
        strdata = s.strdata;
        ++strdata->_refs;
    }
    return *this;
}

str &
str::operator= (char const * s)
{
    if (s != c_ptr())
    {
        short len = (short) strlen (s);
        _chksize (len);
        memcpy (c_ptr(), s, len + 1);
        strdata->_length = len;
    }
    return *this;
}

str &
str::operator= (char c)
{
    _chksize (1);
    *c_ptr() = c;
    strdata->_length = 1;
    return *this;
}

short
str::insert (short pos, char const * s, short len)
{
    if (len < 0)
        len = (short) strlen (s);
    if (len)
    {
        short leng = strdata->_length;
        if (pos < 0 || pos > leng)
            pos = leng;
        _chksize (short(leng + len));
        char * buf = c_ptr();
        if (pos < leng)
            memmove (buf + pos + len, buf + pos, leng - pos);
        memcpy (buf + pos, s, len);
        strdata->_length += len;
    }
    return length();
}

short
str::remove (short pos, short len)
{
    if (pos >= 0 && pos < length())
    {
        short leng = strdata->_length;
        if (len < 0 || (pos + len) > leng)
            len = short(leng - pos);
        if (len)
        {
            _chksize (0);
            char * buf = c_ptr();
            memcpy (buf + pos, buf + pos + len, leng - (pos + len));
            strdata->_length -= len;
        }
    }
    return length();
}

short
str::replace (short pos, char const * s, short clen, short len)
{
    if (pos >= 0)
    {
        short leng = strdata->_length;
        if (clen < 0 || (pos + clen) > leng)
            clen = short(leng - pos);
        if (len < 0)
            len = (short) strlen (s);
        if (pos > leng)
            pos = leng;
        _chksize (short(leng - clen + len));
        char * buf = c_ptr();
        if (clen != len && clen)
            memmove (buf + pos + len, buf + pos + clen,
                     leng - (pos + clen - len));
        if (len)
            memcpy (buf + pos, s, len);
        strdata->_length += short(len - clen);
    }
    return length();
}


str &
str::left (short len, char padch)
{
    if (len < 0)
        return right (short(-len), padch);
    short leng = strdata->_length;
    if (len != leng)
    {
        _chksize (len);
        if (len > leng)
            memset (strdata->ptr() + leng, padch, leng - len);
        strdata->_length = len;
    }
    return *this;
}

str &
str::right (short len, char padch)
{
    if (len < 0)
        return left(-1, padch);
    short leng = strdata->_length;
    if (len != leng)
    {
        _chksize (len);
        if (len > leng)
        {
            char * buf = strdata->ptr();
            memmove (buf + len - leng, buf, leng);
            memset (buf, padch, len - leng);
        }
        strdata->_length = len;
    }
    return *this;
}

str &
str::mid (short pos, short len, char padch)
{
    if (pos <= 0)
        return left(len, padch);
    short leng = strdata->_length;
    if (pos > leng)
        pos = leng;
    if (leng < len)         // Are we padding?
    {
        _chksize (len);
        char * buf = strdata->ptr();
        short nlen = short((len - (leng - pos)) / 2);
        if (nlen > 0)
        {
            memmove (buf, buf + pos, leng - pos);
            memset (buf + leng - pos, padch, nlen);
            strdata->_length -= short(pos - nlen);
        }
    }
    return right (len, padch);
}


int
str::_concat (char const * s, short len)
{
    if (len < 0)
        len = (short) strlen (s);
    if (len)
    {
        _chksize (short(len + length()));
        memcpy (c_ptr() + length(), s, len);
        strdata->_length += len;
    }
    return length();
}

short
str::removech (char const * clist)
{
    short result = 0;
    if (*clist)
    {
        char * buf, * sub;
        buf = sub = strdata->ptr();
        short nlen = strdata->_length;
        for (short i = 0; i < nlen; ++i)
        {
            if (strchr (clist, *buf) == 0)
            {
                if (result)
                    *sub = *buf;
                ++sub;
            }
            else
            {
                if (!result)
                    _chksize (0);
                ++result;
            }
            ++buf;
        }
        strdata->_length = short(nlen - result);
    }
    return result;
}

short
str::countch (char const * clist)
{
    short result = 0;
    if (*clist)
    {
        char * buf = strdata->ptr();
        short nlen = strdata->_length;
        for (short i = 0; i < nlen; ++i, ++buf)
            if (strchr (clist, *buf) != 0)
                ++result;
    }
    return result;
}


str
left (str const & s, short len, char padch)
{
    str n(s);
    return n.left(len, padch);
}

str
right (str const & s, short len, char padch)
{
    str n(s);
    return n.right(len, padch);
}

str
mid (str const & s, short pos, short len, char padch)
{
    str n(s);
    return n.mid(pos, len, padch);
}
