#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "slputils.c"

/* 2kHz-lowpass.c 
Filters infile to produce outfile using a fifth-order IIR filter with coefficients a1-a6 and b1-b6. (For an FIR filter, set a[0..5] to 0.) */

void main(int argc, char *argv[]) {
   char *infile, *outfile;
   int *length, i;
   short int *x, *y, *signal_in();
   float *yf;
   void signal_out();

   /* Coefficients for a low-pass filter */
   /* (<2 kHz at 16000 samples/s) */		
   float a[6] = {0, -3.2290, 4.9745, -4.2083, 1.9758, -0.3978};
   float b[6] = {0.0978, -0.1411, 0.1008, 0.1008, -0.1411, 0.0978};

   if (argc != 3) {
      printf("usage: 2kHz-lowpass input_file output_file\n");
      exit(1);
   }
   infile = argv[1];
   outfile = argv[2];

   x = signal_in(infile,length);
   y = (short *) calloc(*length,sizeof(short int));
   yf = (float *) calloc(*length,sizeof(float));

   for (i = 6 ; i <= *length ; i++) {
      yf[i] = (b[0]*x[i] + b[1]*x[i-1] + b[2]*x[i-2] 
         + b[3]*x[i-3] + b[4]*x[i-4] + b[5]*x[i-5] - a[1]*yf[i-1] 
         - a[2]*yf[i-2] - a[3]*yf[i-3] - a[4]*yf[i-4] - a[5]*yf[i-5]);
      y[i] = (short int) yf[i];
   }

   signal_out(length,y,outfile);
}

