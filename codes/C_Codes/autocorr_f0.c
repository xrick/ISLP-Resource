#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "slputils.c"
#define SR 16000		/* Sampling Rate */
#define MINF0 80
#define MAXF0 180

/* AUTOCORR_F0.C									*/
/* Pitch prediction by short-time autocorrelation. f0_out (the 	*/
/* sample-by-sample f0 track) is written to outfile.			*/

int main(int argc, char *argv[])
{
   short int *x_in, *signal_in(), *f0;
   char *infile, *outfile;
   int i, j, *length, maxlag, bot=SR/MINF0, top=SR/MAXF0;
   void four1(), correl(), signal_out();
   float *data, ans[1025], *x_in_f, max;

   if (argc != 3) {
      printf("usage: autocorr_f0 input_file output_file\n");
      exit(1);
   }
   infile = argv[1];
   outfile = argv[2];

   x_in = signal_in(infile,length);
/* Make a floating-point versions of x_in, called x_in_f, and	*/
/* allocate space	for f0	 						*/
   x_in_f = (float *) calloc(*length,sizeof(float));
   f0 = (short int *) calloc(*length,sizeof(short int));

   for (i=0;i<*length;i++) x_in_f[i] = (float) x_in[i];
   for (i=0;i<=1024;i++) ans[i] = 0;

   printf("Working ...\n");
   for (i=0;i<512;i++) f0[i] = 0;
   for (i=0;i<(*length)-512;i++) {
      data = x_in_f+i-1;
      correl(data,data,512,ans);
      
      maxlag = SR/MAXF0;
      max = 0;
      for (j=top;j<=bot;j++) {
         if (ans[j] > max) {
            maxlag = j;
            max = ans[j];
         }
      }
      f0[i+512] = SR/maxlag;		
/* i+512 to offset lag introduced by windowing */
      if (f0[i+512] >= MAXF0) f0[i+512]=0;
   }
   signal_out(length,f0,outfile);
   return 0;
}

