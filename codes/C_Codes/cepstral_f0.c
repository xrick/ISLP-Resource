#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "slputils.c"
#include "four1.c"

/* CEPSTRAL_F0.C								*/
/* Pitch (f0) tracking using cepstral analysis 					*/
/* An extension of cepstrum.c							*/

/* Reads a signal from a disk file into a variable, x_in. 		 	*/
/* f0 is written as a *text* stream to the standard output.			*/

int main(int argc, char *argv[]) {
	short int *x_in, *signal_in();
	char *infile, *frameno, *endcp;
	int i, *length;
	void four1(), cepstral_f0();
	float max_f0;

	if (argc != 2) {
		printf("usage: cepstral_f0 input_file [ > output_file ]\n");
		exit(1);
	}
	infile = argv[1];
	x_in = signal_in(infile,length);

	printf("Sample\tf_0 (Hz)\n");
	for (i=79;i<319;i+=80) printf("%d\t0\n",i);
	for (i=319;i<*length-256;i+=80)
		cepstral_f0(i,x_in,max_f0);
        return 0;
}

void cepstral_f0(int frame, short int *x_in, float max_f0) {
/* Given a pointer to a signal *x_in and a frame number, returns the 
pitch.	*/

	float data[1024];			/* 512 complex data points	*/
	float wvalue, twopi, arg, max, logpsd[1024];
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

	four1(logpsd-1,512,-1);				/* Inverse FFT	*/

	max = 0.0;
	max_f0 = 0.0;
	for (i=88;i<256;i++){		
/* Work down from an upper limit of 180Hz  (88 = 16000/180)*/
		if (logpsd[2*i] > max) {
			max = logpsd[2*i];
			max_f0 = 16000.0/i;
		}
	}
	printf("%d\t%.1f\n",frame,max_f0);
}

