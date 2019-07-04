/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


Program: REDIR.C
Author:  F. PIETTE (2:293/2201.135)
Object:  Demonstration of the output redirection
Creation: Augustus 2, 1991
Updates:


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(void)
{
    int old_fh;
    int new_fh;

    fprintf(stdout, "This goes to the original standard output\n");

    /* Duplicate the stdout file handle to restore it later */
    old_fh = dup(fileno(stdout));
    if (old_fh == -1) {
         fprintf(stderr, "dup error\n");
         exit(1);
    }

    /* Open the new file for output */
    if ((new_fh = open("redir.txt", O_CREAT | O_TRUNC | O_WRONLY,
                       S_IREAD | S_IWRITE)) == -1) {
         fprintf(stderr, "Unable to open redir.txt\n");
         exit(1);
    }
    /* Duplicate the new handle to stdout */
    dup2(new_fh, fileno(stdout));
    /* We don't need new_fh any more, so close it */
    close(new_fh);

    /* stdout is now redirected, let's try it */
    fprintf(stdout, "This goes to redir.txt file !\n");

    /* If you run a program using spawn(), the child program will have */
    /* its output redirected to REDIR.TXT file ! */

    /* Now let's restore stdout to its original state */
    fflush(stdout);  /* First flush the outut buffer */
    /* Then duplicate the original file handle to stdout */
    dup2(old_fh, fileno(stdout));

    /* Let's try if we canceled the redirection */
    fprintf(stdout, "Back to original stdout\n");

    exit(0);
}
