#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "slputils.c"
#define SR 8000		/* Sampling Rate */

/* DEPITCH.C								*/
/* Pitch prediction by short-time autocorrelation of an LPC residual	*/
/* with subtraction of the correlated samples from the residual		*/

/* John Coleman								*/

void main(int argc, char *argv[])
{
	short int *x_in, *signal_in(), *x_out;
	char *infile, *outfile;
	int i=3760, j, *length, maxlag, bot=SR/60, top=SR/320;
	void four1(), correl(), signal_out();
	float *data, ans[2049], *x_in_f, max;

	if (argc != 3) {
		printf("usage: autocorr input_file output_file\n");
		exit(1);
	}
	infile = argv[1];
	outfile = argv[2];

	x_in = signal_in(infile,length);
/* Make floating-point versions of x_in, called x_in_f and lag		*/
	x_in_f = (float *) calloc(*length,sizeof(float));
	x_out = (short int *) calloc(*length,sizeof(short int));

	for (i=0;i<*length;i++) x_in_f[i] = (float) x_in[i];
	for (i=0;i<=2048;i++) ans[i] = 0;

	printf("Working ...\n");
	for (i=0;i<1024;i++) x_out[i] = 0;

	for (i=1024;i<(*length)-1024;i++) {
		data = x_in_f+i-1;
		correl(data,data,1024,ans);
		
		maxlag = 0;
		max = 0;
		for (j=top;j<=bot;j++) {
			if (ans[j] > max) {
				maxlag = j;
				max = ans[j];
			}
		}
		x_out[i] = x_in[i]-0.08*x_in[i-maxlag+1];
	}
	for (i=(*length)-1024;i<=(*length);i++) x_out[i] = 0;
	signal_out(length,x_out,outfile);
}	
