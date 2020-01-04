#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "slputils.c"
#include "four1.c"
#define SR 16000

/* SPECTRAL_F0.C								*/
/* Pitch (f0) tracking by finding the frequency of the first harmonic		*/

/* Reads a signal from a disk file into a variable, x_in. 		 	*/
/* f0 is written as a *text* stream to the standard output.			*/

void main(int argc, char *argv[])
{
	short int *x_in, *signal_in();
	char *infile;
	int i, *length;
	void four1(), spectral_f0();
	short int f0;

	if (argc != 2) {
		printf("usage: cepstral_f0 input_file [ > output_file]\n");
		exit(1);
	}
	infile = argv[1];

	x_in = signal_in(infile,length);

	printf("Sample\tf_0 (Hz)\n");
	for (i=79;i<320;i+=80) printf("%d\t0\n",i);
	for (i=399;i<*length-256;i+=80)
		spectral_f0(i,x_in,f0);
}

void spectral_f0(int frame, short int *x_in, short int f0) {
/* Given a pointer to a signal *x_in and a frame number, returns the pitch.	*/

	float data[1024];			/* 512 complex data points	*/
	float wvalue, twopi, arg, logpsd[1024];
	int i;

	/* Windowing using 512-point Hanning window and coercion to floats 	*/

	twopi = 8.0*atan(1.0);            		/* calculate 2*PI 	*/
	arg = twopi/511.0;
	for (i=0;i<=511;i++) {
		wvalue = 0.5 - 0.5*cos(arg*i);
		data[2*i] = x_in[frame+i-256] * wvalue;
		data[2*i+1] = 0.0;
	}

	four1(data-1,512,1);

	for (i=0;i<=511;i++) {
		logpsd[2*i] = data[2*i];
		logpsd[2*i] *= logpsd[2*i];
		logpsd[2*i] += SQR(data[2*i+1]);
		logpsd[2*i] = 10*log10(logpsd[2*i]);
		logpsd[2*i+1] = 0.0;
	}
	f0 = 0;
	for (i=0;i<50;i++) {
		if ((logpsd[2*(i+2)]>=logpsd[2*(i+1)]) && (logpsd[2*(i+3)] < logpsd[2*(i+2)])) {
			f0 = (short int) (SR/512)*(i+1);
			break;
		}
	}

	printf("%d\t%d\n",frame,f0);
}

