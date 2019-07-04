/*
**  FSIZE.C - Determine apparent file size of buffered file. Returns size
**            corrected for text mode character translation.
**
**  public domain demo by Bob Stout
*/

#include <stdio.h>
#include <stdlib.h>

long fsize(FILE *fp)
{
      size_t bufsize, bytes_read;
      char *bufptr;
      long size = 0L, pos;

      for (bufsize = 0x8000; NULL == (bufptr = malloc(bufsize)); bufsize /= 2)
            ;
      if (!bufptr)
            return -1L;
      pos = ftell(fp);
      do
      {
            bytes_read = fread(bufptr, sizeof(char), bufsize, fp);
            size += bytes_read;
      } while (bytes_read);
      free(bufptr);
      fseek(fp, pos, SEEK_SET);
      return size;
}

#ifdef TEST

#include <string.h>

#ifdef MSDOS
 #define fl(x) filelength(x)
 #define getsize(fp) fl(fileno(fp))
#else
 #define fl(x) puts("Install compiler-specific file length function here")
 #define getsize(fp) fl(fp)
#endif

int main(int argc, char *argv[])
{
      FILE *fp;
      long size, csize, lsize;
      char buf[256];

      while (--argc)
      {
            if (NULL == (fp = fopen(*++argv, "r")))
                  printf("Can't open %s\n", *argv);

            size = getsize(fp);
            printf("\n\"Real\" size of %s is %ld\n", *argv, size);

            for (csize = 0L; EOF != fgetc(fp); ++csize)
                  ;
            rewind(fp);

            for (lsize = 0L; !feof(fp); )
            {
                  if (NULL != fgets(buf, 256, fp))
                        lsize += strlen(buf);
            }
            rewind(fp);

            printf("fsize() returned a size = %s is %ld\n",
                  *argv, fsize(fp));
            printf("Reading chars returned an apparent size of %ld\n",
                  csize);
            printf("Reading lines returned an apparent size of %ld\n",
                  lsize);
      }
}

#endif
