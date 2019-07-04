/*******************************************************************
 * Generic structure <> disk file manipulations. These functions
 * form a basic template for reading and writing structures to a 
 * sequential file. This template is probably most useful for files
 * with 500 or less records and eliminates the need for a more 
 * elaborate file handler such as C-Tree, DB-Vista, Mix etc.
 * Routines to put data in the struct is out of scope here.
 * Written by Lynn Nash 8/28/91 and donated to the public domain.
 */
#include <io.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 
#ifndef ERROR
#define ERROR -1
#define OK     0
#endif
 
#ifndef TRUE
#define TRUE 1
#define FALSE !TRUE
#endif

/* make sure the record structure is byte aligned */

#if defined(__TURBOC__)
 #pragma option -a-
#elif defined(__ZTC__)
 #pragma ZTC align 1
#else /* MSC/QC/WATCOM/METAWARE */
 #pragma pack(1)
#endif

static struct blackbook {
    int delete_flag;        /* 0 = active  -1 = deleted */
    int recordnum;          /* a sequential number in the file */
   /* The data fields in asciiz.  */
    char firstname[11];         
    char lastname[16];         
    char addr[26];          
    char city[16];
    char state[3];
    char zip[10];
    char phone[11];
} rec, oldrec;             /* 97 byte record  * 2 */

#pragma pack()
 
/*-------------------- general globals ---------------------*/

static long cur_rec = 0;      /* the current record number */
static FILE *fsptr = NULL;    /* fixed record data file pointer */
 
/* if file exists open in read/write mode else create file */

FILE * open_file(char *filename)
{
      if (access(filename, 0) == 0)
            fsptr = fopen(filename, "rb+"); 
      else  fsptr = fopen(filename, "wb+"); 
      return fsptr;                       /* return the file pointer */
} 
 
/* add new records to the data file */

int datadd(void)
{
      if (fsptr)
      {
            if (fseek(fsptr, 0L, SEEK_END) != 0)
                  return ERROR;  /* seek failure */
            rec.delete_flag = 0; /* active record tag */
            rec.recordnum = (int) (ftell(fsptr) / 
                  (long) sizeof(struct blackbook));
            if (fwrite(&rec, sizeof(struct blackbook), 1, fsptr) != 1)
            {
                  return ERROR; /* write error */
            }
            else
            {
                  /* put your clean up code here */ 
                  return OK;
            }
      }
      return ERROR;
}

/* tag the last record read in the file as deleted */

int data_delete(void)
{
      if (fsptr)
      {
            if (fseek(fsptr, (long) sizeof(struct blackbook) * -1L,
                  SEEK_CUR) != 0)
            {
                  return ERROR;
            }
            rec.delete_flag = -1;   /* tag the record as deleted */
            if (fwrite(&rec, sizeof(struct blackbook), 1, fsptr) != 1)
                  return ERROR;
            else  return OK;
      }
      return ERROR;
}

/* read a random structure. If successful the global cur_rec will 
 * contain the number of the last record read & it can be compared
 * to the number in the struct as a double check (belt & suspenders)
 */

int data_read(long recnum)
{
      if (fseek(fsptr, (long) sizeof(struct blackbook) * recnum,
            SEEK_SET) != 0)
      {
            return ERROR;
      }
      cur_rec = recnum; /* keep tabs on record pointer in global */  

      /* now read the record into save struct*/

      if (fread(&oldrec, sizeof(struct blackbook), 1, fsptr) != 1)
      {
            return ERROR;
      }
      else                          /* copy save struct to edit struct */
      {
            memcpy(&rec, &oldrec, sizeof(struct blackbook));
            return OK;
      }
}
 
/* rewrite the last read record back to disk */

int data_update(void)
{
      if (memcmp(&rec, &oldrec, sizeof(struct blackbook)) == 0)
            return TRUE;  /* no update needed */

      /* back up one record before writing */

      if (fseek(fsptr, (long) sizeof(struct blackbook) * -1L, 
            SEEK_CUR) != 0)
      {
            return ERROR; /* seek error */ 
      }

      /* now write the record */

      if (fwrite(&rec, sizeof(struct blackbook), 1, fsptr) != 1)
            return ERROR; /* write error */
      return OK;
}

/* get the next valid record in the file */

int read_forward(void)
{
      do
      {
            cur_rec++; /* upcount the record number */
            if (data_read(cur_rec) != 0)
            {
                  cur_rec--; /* decrement the record number */
                  return ERROR;
            }
      } while (oldrec.delete_flag != 0); /* record read was deleted */
      return OK;
}

/* get the previous valid record in the file */

int read_backward(void)
{
      do
      {
            cur_rec--;  /* decrement the record number */
            if (cur_rec >= 0)
            {
                  if ( data_read(cur_rec) != 0 )
                  {
                        cur_rec++; /* increment the record number */
                        return ERROR;
                  }
            }  
      } while (oldrec.delete_flag != 0); /* record read was deleted */
      return OK;
}
