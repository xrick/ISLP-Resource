#include <stdio.h>
#include <math.h>
#include "slputils.c"

/* RMS.C */

/* Reads a signal (a sequence of shorts in "Intel" format) from 
a disk file into an array, x. The length of the signal is returned in 
*length. Calculates and prints out the root mean square amplitude of 
the signal. */

int main(int argc, char *argv[]) {
	    short int *x, *signal_in();
    char *infile;
    int i, *length, n;
    float rms = 0.0, sum = 0.0;

    if (argc != 2) {
        printf("usage: rms input_file\n");
        exit(1);
    }
    infile = argv[1];
    x = signal_in(infile,length);
    n = *length; 

    for (i=0;i<n;i++)
        /* Square x[i] and add it to the sum-so-far */
        sum += (float) x[i] * (float) x[i]; 
    rms = sqrt(sum/ (float) n);
    printf("The RMS amplitude of %s is %.2f\n",infile,rms);
    return 0;
}

