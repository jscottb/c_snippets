#include <stdio.h>
#include <string.h>

/* --------------------------------------------------------------------
   Module:     WHICHARC.C
   Subject:    tries to determine the archiver used to compress files
   Author:     Heinz Ozwirk & David Gersic
               modified for SNIPPETS by Bob Stout
   Status:     public domain
   Started:    28.09.1991   13:35:57
   Modified:   13.10.1991   14:15:57
   Modified:   5 January, 1992 11:50am by David Gersic
                   Added return codes for self extracting archive files.
   Modified:   16 January, 1992, 4:15pm by David Gersic
                   Added Pak and ARC ver. 6 with information from Richard
                   Vanhouten @1:272/38. I'm not sure that this code works
                   perfectly for those formats, as his message seems to
                   indicate that the entire archive has to be scanned for
                   headers to check before the type can be perfectly
                   determined. It seems to work for test archives produced
                   here, but may not work for all archives.
   --------------------------------------------------------------------
   Prototype:  int WhichArc(char *pName)
      pName    address of full path name of file to examine
      Result   -1:      file not found
               UNKNOWN: unknown packer
               ARC:     ARC or PKARC
               ARJ:     ARJ
               LHA:     LHARC or LHA
               ZIP:     PKZIP
               ZOO:     Zoo
               PAK:     Pak
               ARC7:    ARC later than ver. 6.02
               SFXARC:  Self Extracting PKARC
               SFXARJ:  Self Extracting ARJ
               SFXLHARC:Self Extracting LHARC
               SFXLHA:  Self Extracting LHA
               SFXZIP:  Self Extracting ZIP
               SFXPAK:  Self Extracting Pak
               SFXARC6: Self Extracting ARC later than ver. 6.02
               EXE:     MS DOS executable of unknown type

   LHARC/LHA
      No archive header. WhichArc examines the checksum of the first
      file header. If the checksum is valid and if the string -lh?-
      is found, LHA or LHARC is assumed.

   ARJ
      If a file starts with 0x60, 0xEA, ARJ is assumed.

   ZIP
      If the file begins with "PK", PKZIP is assumed.

   ZOO
      Zoo'ed archives always start with "ZOO x.xx Archive". WhichArc
      only looks for "ZOO".

   ARC
      No header. Files starting with 0x1A are assumed to be ARCed.

   PAK
      Similar to ARC files, but if the second byte of the header is 0x0a or
      0x0b, it was created by Pak.

   ARC7
      Similar to ARC, but if the second byte of the header is 0x14 or
      higher, it was created by an Arc version later than 6.02.

   SFX*
      All of the SFX files start with a small decompressor. Seek past
      the decompressor and repeat the above checks. 
   -------------------------------------------------------------------- */


typedef unsigned char BYTE;

enum ArcType { ArcERR=-1, UNKNOWN, ARC, ZOO, ARJ, LHARC, LHA, ZIP, PAK, ARC7,
               SFXARC, SFXARJ, SFXLHARC, SFXLHA, SFXZIP, SFXARC7, SFXPAK, EXE
             };

enum ArcType WhichArc(char *pName)
{
      FILE  *fp;
      BYTE  header[128];
      int   c, i, n;
      enum  ArcType retval = ArcERR;

      memset(header, 0, sizeof(header));
      fp = fopen(pName, "rb");
      if (fp == NULL)
            goto EXIT;                                /* error opening file */
      n = fread(header, sizeof(BYTE), sizeof(header) - sizeof(BYTE), fp);

      if (n <= 0)                               /* error reading from file  */
            goto EXIT;

      if (n >= 7 && n >= header[0] + 2)
      {
            for (c = 0, i = header[0]; i--; c += (header+2)[i])
                  ;
            if (((BYTE)(c & 0x00FF)) == header[1] 
                  && header[2] == '-' 
                  && header[3] == 'l' 
                  && header[4] == 'h' 
                  && header[6] == '-')
            {
                  retval = (header[5] > '1') ? LHA : LHARC;
                  goto EXIT;
            }
      }

      if (n >= 2)
      {
            if (header[0] == 0x60 && header[1] == 0xEA)
            {
                  retval = ARJ;
                  goto EXIT;
            }
            if (header[0] == 'P'  && header[1] == 'K')
            {
                  retval = ZIP;
                  goto EXIT;
            }
      }

      if (n >= 3 && header[0] == 'Z' && header[1] == 'O' && header[2] == 'O')
      {
            retval = ZOO;
            goto EXIT;
      }

      if (n >= 25 && header[0] == 0x1A)
      {
            if (header[1]>0x14)
                  retval = ARC7;
            else if (header[1]==0x0a || header[1]==0x0b)
                  retval = PAK;
            else  retval = ARC;
            goto EXIT;
      }

      if (0 == strncmp(header, "MZ", 2))        /* some sort of .EXE file   */
      {
            /* test for SFX ARJ file */

            memset(header, 0, sizeof(header));
            fseek(fp, 0x39ba, SEEK_SET);
            n = fread(header, sizeof(BYTE),
                  sizeof(header) - sizeof(BYTE), fp);
            if (n > 1 && header[0] == 0x60 && header[1] == 0xea)
            {
                  retval = SFXARJ;
                  goto EXIT;
            }

            /* test for SFX LHARC file */

            memset(header, 0, sizeof(header));
            fseek(fp, 0x653, SEEK_SET);
            n = fread(header, sizeof(BYTE),
                  sizeof(header) - sizeof(BYTE), fp);
            for (c = 0, i = header[0]; i--; c += (header+2)[i])
                  ;
            if (n >= 7 && n >= header[0] + 2)
            {
                  if (((BYTE)(c & 0x00FF)) == header[1] 
                        && header[2] == '-' 
                        && header[3] == 'l' 
                        && header[4] == 'h' 
                        && header[6] == '-')
                  {
                        retval = SFXLHARC;
                        goto EXIT;
                  }
            }

            /* test for SFX LHA file */

            memset(header, 0, sizeof(header));
            fseek(fp, 0x799, SEEK_SET);
            n = fread(header, sizeof(BYTE),
                  sizeof(header) - sizeof(BYTE), fp);
            for (c = 0, i = header[0]; i--; c += (header+2)[i])
                  ;
            if (n >= 7 && n >= header[0] + 2)
            {
                  if (((BYTE)(c & 0x00FF)) == header[1] 
                        && header[2] == '-' 
                        && header[3] == 'l' 
                        && header[4] == 'h' 
                        && header[6] == '-')
                  {
                        retval = SFXLHA;
                        goto EXIT;
                  }
            }

            /* test for SFX ZIP file */

            memset(header, 0, sizeof(header));
            fseek(fp, 0x31f0, SEEK_SET);
            n = fread(header, sizeof(BYTE),
                  sizeof(header) - sizeof(BYTE), fp);
            if (n > 1 && header[0] == 'P'  && header[1] == 'K')
            {
                  retval = SFXZIP;
                  goto EXIT;
            }

            /* test for SFX PKARC file */

            memset(header, 0, sizeof(header));
            fseek(fp,0x261e,SEEK_SET);
            n = fread(header, sizeof(BYTE),
                  sizeof(header) - sizeof(BYTE), fp);
            if (n > 1 && header[0] == 0x1a)
            {
                  if (header[1]>0x14)
                        retval = SFXARC7;
                  else if (header[1]==0x0a || header[1]==0x0b)
                        retval = SFXPAK;
                  else  retval = SFXARC;
            }
            else  retval = EXE;
      }
      retval = UNKNOWN;
EXIT: fclose(fp);
      return retval;
}

#ifdef TEST

int main(int argc,char *argv[])
{
      char *arc_types[]={"UNKNOWN", "ARC", "ZOO", "ARJ", "LHARC", "LHA",
                         "ZIP", "PAK", "PAK", "ARC7", "SFXARC", "SFXARJ",
                         "SFXLHARC", "SFXLHA", "SFXZIP", "SFXARC7", "SFXPAK",
                         "EXE"};

      while (--argc)
      {
            enum ArcType which;

            if (ArcERR == (which = WhichArc(*++argv)))
                  printf("File error accessing %s\n", *argv);
            else  printf("%s archive type is %s\n", *argv, arc_types[which]);
      }
      return(0);
}

#endif
