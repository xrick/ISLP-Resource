#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "slputils.c"

/* RMS_AMPLITUDE.C 
Calculates the sample-by-sample root mean square amplitude of infile 
over an 80-sample window, and writes the result to outfile. */

void main(int argc, char *argv[]) {
   char *infile, *outfile;
   int *length, i, end;
   short int *x, *y, *signal_in();
   float sum;
   void signal_out();

   if (argc != 3) {
      printf("usage: magnitude input_file output_file\n");
      exit(1);
   }
   infile = argv[1];
   outfile = argv[2];

   x = signal_in(infile,length);
   y = (short int *) calloc(*length,sizeof(short int));

   for (i = 0; i < 79; i++) y[i] = sqrt(x[i]*x[i]);
   for (end = 79 ; end < *length; end++) {
      sum = 0;
      for (i = end-79; i <= end; i++)
         sum += (x[i]*x[i])/80;
      y[i] = (short int) sqrt(sum);
   }

   signal_out(length,y,outfile);
}

