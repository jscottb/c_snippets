//
// Simple string class
// Public domain
//
// Written by david nugent
// davidn@csource.pronet.com
// 3:632/348@fidonet
//

# if !defined( _str_h )
# define _str_h 1

# if defined( __BORLANDC__ ) && ( __BORLANDC__ <= 0x0300 )
# define PLACEMENT_NEW_BUG
# define SIGNED_CHAR_BUG
# endif


struct refstr
{
    short _size;
    short _length;
    short _refs;
    refstr (short length, short size)
        : _length(length), _size(size), _refs(1)
        {}
    ~refstr (void) {}
# if !defined( PLACEMENT_NEW_BUG )
    void * operator new(unsigned sz, short allocsz);
# endif
    char * ptr (void)
    {
        return ((char *)this) + sizeof(refstr);
    }
};




class str
{

  public:

        // constructors/destructors

    str (void)
    {
        _strinit();
    }

    str (char const * s, short len =-1)
    {
        _strinit(s, len, -1);
    }

    str (unsigned char const * s, short len =-1)
    {
        _strinit((char const *)s, len, -1);
    }
# if !defined( SIGNED_CHAR_BUG )
    str (signed char const * s, short len =-1)
    {
        _strinit((char const *)s, len, -1);
    }
# endif

    str (char c)
    {
        _strinit (&c, 1, -1);
    }

    str (unsigned char c)
    {
        _strinit ((char const *)&c, 1, -1);
    }
# if !defined( SIGNED_CHAR_BUG )
    str (signed char c)
    {
        _strinit ((char const *)&c, 1, -1);
    }
# endif
    str (str const & s)
      : strdata(s.strdata)
    {
        ++strdata->_refs;
    }

    ~str (void)
    {
        if (!--strdata->_refs)
            delete strdata;
    }

        // assignment

    str & operator= (str const & s);
    str & operator= (char const * s);
    str & operator= (char c);

    str & operator= (unsigned char const * s)
    {
        return operator= ((char const *)s);
    }
# if !defined( SIGNED_CHAR_BUG )
    str & operator= (signed char const * s)
    {
        return operator= ((char const *)s);
    }
# endif

        // primitive members

    short length (void) const
    {
        return strdata->_length;
    }

    short size (void) const
    {
        return strdata->_size;
    }

        // operators

    str & operator<< (char const * s)   // concatenate
    {
        _concat (s);
        return *this;
    }

    str & operator<< (unsigned char const * s)
    {
        _concat ((char const *)s);
        return *this;
    }
# if !defined( SIGNED_CHAR_BUG )
    str & operator<< (signed char const * s)
    {
        _concat ((char const *)s);
        return *this;
    }
# endif
    str & operator<< (str const & s)
    {
        _concat (s);
        return *this;
    }

    str & operator<< (char c)
    {
        _concat (c);
        return *this;
    }

    str & operator<< (unsigned char c)
    {
        _concat (c);
        return *this;
    }

# if !defined( SIGNED_CHAR_BUG )
    str & operator<< (signed char c)
    {
        _concat (c);
        return *this;
    }
# endif

    char & operator[] (short pos)
    {
        if (pos < 0 || pos >= strdata->_length)
        {
            char * buf = c_ptr() + length();
            *buf = 0;
            return *buf;
        }
        return c_ptr()[pos];
    }

    char * c_ptr (void) const   // not necessarily NUL terminated!
    {                           // Use with caution...
        return strdata->ptr();
    }

    char const * c_str (void) const    // return char*
    {
        char * buf = c_ptr();
        buf[strdata->_length] = 0;
        return buf;
    }

    unsigned char const * u_str (void) const
    {
        return (unsigned char const *)c_str();
    }

        // manipulators

    short insert (short pos, char const * s, short len =-1);

    short insert (short pos, str const & s)
    {
        return insert (pos, s.c_ptr(), s.length());
    }

    short insert (short pos, unsigned char const * s,
                    short len =-1)
    {
        return insert (pos, (char const *)s, len);
    }
# if !defined( SIGNED_CHAR_BUG )
    short insert (short pos, signed char const * s,
                    short len =-1)
    {
        return insert (pos, (char const *)s, len);
    }
# endif
    short insert (short pos, char c)
    {
        return insert (pos, &c, 1);
    }

    short insert (short pos, unsigned char c)
    {
        return insert (pos, (char const *)&c, 1);
    }
# if !defined( SIGNED_CHAR_BUG )
    short insert (short pos, signed char c)
    {
        return insert (pos, (char const *)&c, 1);
    }
# endif

    short remove (short pos =0, short len =-1);

    short replace (short pos, char const * s, short clen =-1,
                    short len =-1);

    short replace (short pos, str & s, short clen =-1)
    {
        return replace (pos, s.c_ptr(), clen, s.length());
    }

    short replace (short pos, unsigned char const * s,
                    short clen =-1, short len =-1)
    {
        return replace (pos, (char const *)s, clen, len);
    }
# if !defined( SIGNED_CHAR_BUG )
    short replace (short pos, signed char const * s,
                    short clen =-1, short len =-1)
    {
        return replace (pos, (char const *)s, clen, len);
    }
# endif
    short replace (short pos, char c, short clen =-1)
    {
        return replace (pos, &c, clen, 1);
    }

    short replace (short pos, unsigned char c, short clen =-1)
    {
        return replace (pos, (char const *)&c, clen, 1);
    }
# if !defined( SIGNED_CHAR_BUG )
    short replace (short pos, signed char c, short clen =-1)
    {
        return replace (pos, (char const *)&c, clen, 1);
    }
# endif

    str & left (short len, char padch =' ');
    str & right (short len, char padch =' ');
    str & mid (short pos, short len, char padch =' ');

    short removech (char const * clist ="\r\n");
    short countch (char const * clist);

  protected:

    refstr * strdata;

    // Check to see if big enough for size
    int _chksize (short sz =0);

    int _concat (char const * s, short len =-1);

    int _concat (str const & s)
    {
        return _concat (s.c_ptr(), s.length());
    }

    int _concat (char ch)
    {
        return _concat (&ch, 1);
    }

    int _concat (unsigned char const * s, short len =-1)
    {
        return _concat ((char const *)s, len);
    }
# if !defined( SIGNED_CHAR_BUG )
    int _concat (signed char const * s, short len =-1)
    {
        return _concat ((char const *)s, len);
    }
# endif

  private:
        // Common constructor
    void _strinit (char const * s =0, short slen =0,
                    short siz =-1);

};


str left (str const & s, short len, char padch =' ');
str right (str const & s, short len, char padch =' ');
str mid (str const & s, short pos, short len, char padch =' ');

# endif
