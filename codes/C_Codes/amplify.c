#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "slputils.c"

/* AMPLIFY.C 
Multiplies the amplitude of infile by a constant. */

void main(int argc, char *argv[]) {
   char *infile, *outfile, *endcp;
   int *length, i;
   double factor;
   short int *x, *y, *signal_in();
   void signal_out();

   if (argc != 4) {
      printf("usage: amplify input_file integer_factor output_file\n");
      exit(1);
   }
   infile = argv[1];
   factor = strtod(argv[2],&endcp);
   outfile = argv[3];

   x = signal_in(infile,length);
   y = (short *) calloc(*length,sizeof(short int));

   for (i = 0 ; i < *length; i++) {
      y[i] = (short int) x[i]*factor;
   }

   signal_out(length,y,outfile);
}

