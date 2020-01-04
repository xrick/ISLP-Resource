#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "slputils.c"

/* DIVIDE.C 
Divides the amplitude of infile1 by infile2 and writes the result to outfile. */

void main(int argc, char *argv[]) {
   char *infile1, *infile2, *outfile;
   int *length1, *length2, *length3, i;
   short int *x1, *x2, *y, *signal_in();
   void signal_out();

   if (argc != 4) {
      printf("usage: divide input_file1 input_file2 output_file\n");
      exit(1);
   }
   infile1 = argv[1];
   infile2 = argv[2];
   outfile = argv[3];

   x1 = signal_in(infile1,length1);
   x2 = signal_in(infile2,length2);
   if (*length1 > *length2) *length3 = *length2;
   else *length3 = *length1;
   y = (short *) calloc(*length3,sizeof(short int));

   for (i = 0 ; i < *length3; i++) {
      y[i] = x1[i]/(x2[i]+1);	/* Add one to prevent division by zero */
   }

   signal_out(length3,y,outfile);
}

