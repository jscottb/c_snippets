/****************************************************************/
/*                                                              */
/*      S-CODER - Encrypt/decrypt data                          */
/*                                                              */
/*      Copyright 1987-1989 by Robert B. Stout dba MicroFirm    */
/*                                                              */
/*      Originally written by Bob Stout with modifications      */
/*      suggested by Mike Smedley.                              */
/*                                                              */
/*      This code may be used freely in any program for any     */
/*      application, personal or commercial.                    */
/*                                                              */
/*  Current commercial availability:                            */
/*                                                              */
/*      1. MicroFirm Toolkit ver 3.00: LYNX and CRYPT utilities */
/*      2. CXL libraries (MSC, TC, ZTC/C++, PC): fcrypt()       */
/*         dedicated file encryption function                   */
/*      3. SMTC & MFLZT libraries: crypt() function             */
/*                                                              */
/****************************************************************/
 
char *cryptext;         /* The actual encryption/decryption key */
int   crypt_ptr = 0;    /* Circular pointer to elements of key  */
int   crypt_length;     /* Set externally to strlen(cryptext)   */
 
/* NOTES: cryptext should be set and qualified (to something over
          5-6 chars, minimum) by the calling program, which should
          also set crypt_ptr in the range of 0 to strlen(cryptext)
          before each use. If crypt() is used to encrypt several
          buffers, cryptext should be reloaded and crypt_ptr reset
          before each buffer is encrypted. The encryption is both
          reversible - to decrypt data, pass it back through crypt()
          using the original key and original initial value of
          crypt_ptr - and multiple passes are commutative.
*/
 
/**** Encrypt/decrypt buffer datum ******************************/
void crypt(unsigned char *buf)
{
      *buf ^= cryptext[crypt_ptr] ^ (cryptext[0] * crypt_ptr);
      cryptext[crypt_ptr] += ((crypt_ptr < (crypt_length - 1)) ?
            cryptext[crypt_ptr + 1] : cryptext[0]);
      if (!cryptext[crypt_ptr])
            cryptext[crypt_ptr] += 1;
      if (++crypt_ptr >= crypt_length)
            crypt_ptr = 0;
}
 
/**** Encrypt/decrypt buffer ************************************/
void bufcrypt(unsigned char *buf, long length)
{
      while (length--)
            crypt(*buf++)
}

#ifdef TEST

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
      static char buf[16384];
      size_t len, i;
      FILE *in, *out;

      if (4 > argc)
      {
            puts("Usage: CRYPT password infile outfile");
            return -1;
      }
      cryptext = argv[1];
      crypt_length = strlen(cryptext);
      if (NULL == (in = fopen(argv[2], "rb")))
      {
            printf("Can't open %s for input\n", argv[2]);
            return -1;
      }
      if (NULL == (out = fopen(argv[3], "wb")))
      {
            printf("Can't open %s for output\n", argv[3]);
            return -1;
      }
      do
      {
            if (0 != (len = fread(buf, 1, 16384, in)))
            {
                  for (i = 0; i < len; ++i)
                        crypt(&buf[i]);
                  fwrite(buf, 1, len, out);
            }
      } while (len);
      fclose(in);
      fclose(out);
      return 0;
}

#endif
