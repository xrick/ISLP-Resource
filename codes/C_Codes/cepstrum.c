#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "slputils.c"
#include "four1.c"

/* CEPSTRUM.C									*/
/* Cepstral analysis								*/
/* An extension of spectrum.c							*/

/* Reads a signal from a disk file into a variable, x_in, and a	*/ 
/* frame number n. Windows the signal using a Hanning window,	*/ 
/* calculates the FFT, the log power spectral density, and then	*/
/* the inverse Fourier transform. The lower half is written as a */
/* text stream to the standard output.				*/

int main(int argc, char *argv[])
{
	short int *x_in, *signal_in();
	char *infile, *frameno, *endcp;
	int frame, i, *length;
	float wvalue, twopi, arg, logpsd[1024];
	float data[1024];			/* 512 complex data points	*/
	void four1();

	if (argc != 3) {
		printf("usage: cepstrum input_file frame_number [ > output_file ]\n");
		exit(1);
	}
	infile = argv[1];
	frameno = argv[2];

	x_in = signal_in(infile,length);
	frame = (int) strtoul(frameno,&endcp,10);

	/* 512-point Hanning windowing and coercion to floats */

	twopi = 8.0*atan(1.0);            	/* calculate 2*PI 	*/
	arg = twopi/511.0;
	for (i=0;i<=511;i++) {
		wvalue = 0.5 - 0.5*cos(arg*i);
		data[2*i] = (float) (x_in[frame+i-256] * wvalue);
		data[2*i+1] = 0.0;
	}

	four1(data-1,512,1);

/* So far, this is all the same as spectrum.c				*/

	for (i=0;i<=511;i++) {
		logpsd[2*i] = data[2*i];
		logpsd[2*i] *= logpsd[2*i];
		logpsd[2*i] += SQR(data[2*i+1]);
		logpsd[2*i] = 10*log10(logpsd[2*i]);
		logpsd[2*i+1] = 0.0;
	}

/* This is additional to spectrum.c						*/

	four1(logpsd-1,512,-1);				/* Inverse FFT	*/

	printf("Quefrency (ms)\tf (Hz)\tAmplitude\n");
	for (i=2;i<256;i++)
		printf("%f\t%.1f\t%f\n",i*0.0625,16000.0/i,logpsd[2*i]);
        return 0;
}

