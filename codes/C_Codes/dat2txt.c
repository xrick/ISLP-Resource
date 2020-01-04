#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "slputils.c"

/* DAT2TXT.C - Converts infile (a signal encoded as shorts) to produce a text stream. */

void main(int argc, char *argv[]) {
   char *infile;
   int i, *length;
   short int *x, *signal_in();

   if (argc != 2) {
      printf("usage: dat2txt input_file [ > output_file]\n");
      exit(1);
   }
   infile = argv[1];
 
   x = signal_in(infile,length);

   for (i = 0 ; i <= *length ; i++)
	printf("%d\n",x[i]);
}

