#include <stdio.h>

/* HALVE_SIGNAL.C								*/
/* Reads a signal from a disk file into a variable, x_in			*/
/* The length of the signal (in shorts) is stored in x_in[0], 			*/
/* and the remainder in x_in[1..n]						*/
/* Halves samples of x_in, putting them into x_out, and writes x_out to disk.	*/
/* Based on a program listing in Embree and Kimble (1991:104)			*/

void main(int argc, char *argv[])
{
	short int size, *x_in, *x_out, *signal_in();
	char *infile;
	char *outfile;
	int i;
	void signal_out();

	if (argc != 3) {
		printf("syntax: halve_signal input_file output_file\n");
		exit(1);
	}
	infile = argv[1];
	outfile = argv[2];

	x_in = signal_in(infile);
	
/* Allocate memory for the output signal - quite unnecessary, but makes this 	*/
/* a useful template for more complicated functions on signals.			*/

	x_out = (short *) calloc(x_in[0],sizeof(short int));
	size = x_in[0];

	for (i=0;i<=x_in[0];i++) x_out[i] = x_in[i+1]/2;

	signal_out(size,x_out,outfile);
}

short int *signal_in(filename)
	char *filename;
{
	FILE *fid;
	int j;
	int status;
	short int input, size, *x_in;

/* Open the file */

	fid = fopen(filename,"rb");
	if(fid == NULL) {
		printf("Error opening %s\n",filename);
		exit(1);
	}

/* First read in shorts, until the end of the file is reached, just to measure the file */

	size = 0;
	
	while(!feof(fid)) {
		status = fread(&input,sizeof(short int),1,fid);
		size++;
		if(status != 1) {
			printf("%s appears to consist of %d shorts\n",filename,size-1);
			break;
		}
	}
	fclose(fid);

/* Allocate memory, and read in the file again	*/

	x_in = (short *) calloc(size,sizeof(short int));
	x_in[0] = size-1;

/* Open the file again */

	fid = fopen(filename,"rb");
	if(fid == NULL) {
		printf("Error re-opening %s\n",filename);
		exit(1);
	}

	for(j=1;j<size;j++) {
		status = fread(&input,sizeof(short int),1,fid);
		x_in[j] = input;
		if(status != 1) {
			printf("Read error at sample %d\n",j);
			exit(1);
		}
	}
	printf("%d frames read in OK\n",j-1);
	fclose(fid);
	return(x_in);
}

void signal_out(size,x_out,outfile)
	int size;
	short int *x_out;
	char *outfile;
{
	FILE *fid;
	int status;

	fid = fopen(outfile,"wb");
	if(fid == NULL) exit(1);

	status = fwrite(x_out,sizeof(short int),size,fid);
	if(status == -1) {
		printf("Error writing %s\n",outfile);	
		exit(1);
	}
	else printf("%s written OK\n",outfile);
	fclose(fid);
}
