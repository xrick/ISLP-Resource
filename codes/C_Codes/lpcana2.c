#include <stdio.h>
#include "slputils.c"
#define k 14		/* Number of coefficients */

/* LPCANA2.C									*/
/* Reads a signal from a disk file into a variable, x_in.			*/
/* Steps through x_in, 80 frames at a time, computes k LPC coefficients in	*/
/* c and writes the LPC coefficients to outfile.				*/

void main(int argc, char *argv[])
{
	short int n_frames, *x_in, *signal_in(), *x_out, *e_out;
	char *infile, *outfile, *errfile;
	int frame, i, j, n, prev, next, *length;
	float data[81], *xms, d[k+1], *c, *x_in_f, *lp, *e;
	void signal_out();
	void memcof();

	if (argc != 4) {
		printf("usage: lpcana input_file coeffs_file lp_error_file\n");
		exit(1);
	}
	infile = argv[1];
	outfile = argv[2];
	errfile = argv[3];

	x_in = signal_in(infile,length);
	n_frames = (*length)/80;

/* Make a floating-point version of x_in, called x_in_f			*/
	x_in_f = (float *) calloc(*length,sizeof(float));
	for (i=0;i<=*length;i++)
		x_in_f[i] = (float) x_in[i];
	c = (float *) calloc((*length)*k,sizeof(float));
/*	printf("memory for c allocated: %d floats\n",(*length)*k);	*/

	for (frame=0;frame<n_frames;frame++) {
		for (j=0;j<=79;j++)
			data[j+1] = x_in_f[80*frame+j];
		memcof(data,80,k,&xms,d);
		for (j=0;j<=k-1;j++) {
			c[(frame+1)*80*k-k+j] = d[j+1];
			printf("%f ",d[j+1]);
		}
	printf("\n");
	}

/* For the first LPC frame, use the first analysis vector for every sample	*/

	for (i=0;i<=78;i++) {
		for (j=0;j<=k-1;j++) {
			c[i*k+j] = c[79*k+j];
		}
	}

/* For frames 1..n_frames, interpolate the intermediate LPC vectors		*/
	for (frame=1;frame<n_frames;frame++) {
		prev = frame*k*80-k;
		next = prev+k*80;
		for (i=0;i<79;i++) {
			for (j=0;j<=k-1;j++) {
				c[prev+k+k*i+j] = c[prev+j]+((float) i/80.0)*(c[prev+j]-c[next+j]);
			}
		}
	}

/* Model x_in_f and calculate the error						*/
	lp = (float *) calloc(*length,sizeof(float));	/* predicted signal	*/
	e = (float *) calloc(*length,sizeof(float));	/* error signal		*/
	x_out = (short int *) calloc(*length,sizeof(short int));
	e_out = (short int *) calloc(*length,sizeof(short int));

	for (i=k;i<=(*length)-k;i++) {
		j = (i-1)*k;
		lp[i] = 0;
		for (n=0;n<=k-1;n++)
			lp[i] = lp[i] -c[j+n]*lp[i-n-1];
		lp[i] = -lp[i];

		e[i] = x_in_f[i]-lp[i];
		x_out[i] = (short int) lp[i];
		lp[i] += e[i];
		e_out[i] = (short int) e[i];
	}

	signal_out(length,x_out,outfile);
	signal_out(length,e_out,errfile);
}

