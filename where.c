/*
**  WHERE.C:  will search all DIRs on the given drive for specified file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <string.h>

#if defined(__ZTC__)
 #include <direct.h>
 #define GetDrive(d) dos_getdrive(&d)
 #define SetDrive(d) {unsigned x;dos_setdrive(d,&x);}
 #define FAR _far
#elif defined(__TURBOC__)
 #include <dir.h>
 #define GetDrive(d) ((d) = getdisk() + 1)
 #define SetDrive(d) (setdisk(d - 1))
 #define FAR far
 #define _dos_findfirst(f,a,b) findfirst(f,b,a)
 #define _dos_findnext(b) findnext(b)
 #define find_t ffblk
 #define _A_SUBDIR FA_DIREC
 #define attrib ff_attrib
 #define name ff_name
#else /* assume MSC */
 #include <direct.h>
 #define GetDrive(d) _dos_getdrive(&d)
 #define SetDrive(d) {unsigned x;_dos_setdrive(d,&x);}
 #define FAR _far
#endif

int count=0;

main(int argc, char *argv[])
{
      char *curdir,
            sought[80],
           *temp;
      int   curdrive, newdrive, p;
      void  searchdir(char *dir, char *ptrn);

      /*  Find out where we are */

      curdir=getcwd(NULL,80);
      GetDrive(curdrive);

      /*  Find out what we're looking for  */

      if(argc>1)
            strcpy(sought,argv[1]);
      else
      {
            printf("\n\nPattern to search for: ");
            gets(sought);
      }

      /*  Get designator for another drive if specified  */

      if(sought[1]==':')
      {
            newdrive=(toupper(sought[0]))-64;       /* convert  */
            SetDrive(newdrive);
            p = (sought[2]=='\\') ? 3:2;
            strcpy(sought, &(sought[p]));
      }

      /*  Add wildcard prefix/suffix if necessary  */

      if(sought[0]=='.')
      {
            temp=strcat("*",sought);        /*  set prefix  */
            strcpy(sought,temp);
      }
      if(!strchr(sought,'.'))
            strcpy(sought,"*.*");           /*  set suffix  */

      /*  Perform search for pattern starting in root  */

      searchdir("\\",sought);
      printf("\nNumber of matches: %d",count);

      /*  Restore Original Drive and Directory  */

      SetDrive(curdrive);
      chdir(curdir);
      return EXIT_SUCCESS;
}

/*------------------------------------------------------------------------- */

void searchdir(char *path, char *ptrn)
#define ANYFILE 0xFF                         /*  recursive routine  */
{
      struct find_t *f;
      char          *wholepath;
      unsigned      rtn;

      chdir(path);                    /*  change to new path  */
      wholepath=getcwd(NULL,80);      /*  get full path name  */
      f=malloc(sizeof(*f));

      /*  Search for filename matches in this directory  */

      rtn= _dos_findfirst(ptrn,ANYFILE,f);
      while(rtn==0)
      {
            if( f->attrib != _A_SUBDIR )
                  printf("%s\\%s\n",wholepath,f->name);
            else  printf("%s\\%s <DIR>\n",wholepath, f->name);
            ++count;

            rtn = _dos_findnext(f);         /* find next match  */
      }  /* end while loop  */

      /*  Now search any subdirectories under this directory  */

      rtn= _dos_findfirst("*.*", _A_SUBDIR,f);
      while(rtn==0)
      {
            if( (f->attrib == _A_SUBDIR) && (f->name[0] != '.'))
            {
                  searchdir(f->name,ptrn);   /* recursive call */
                  chdir(wholepath);
            }
            rtn = _dos_findnext(f);  /* search next dir  */
      }

      free(wholepath);
      free(f);
}
