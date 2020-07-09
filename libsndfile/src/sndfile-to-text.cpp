/**
 * libsndfile sample
 * 2020-03-01 K.OHWADA
 */

// convert audio fitl to text file
// original : https://github.com/erikd/libsndfile/blob/master/examples/sndfile-to-text.c

/*
** Copyright (C) 2008-2016 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in
**       the documentation and/or other materials provided with the
**       distribution.
**     * Neither the author nor the names of any contributors may be used
**       to endorse or promote products derived from this software without
**       specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#include <sndfile.h>

#include "parse_filename.hpp"

using namespace std;


#define	BLOCK_SIZE 4096

#ifdef DBL_DECIMAL_DIG
	#define OP_DBL_Digs (DBL_DECIMAL_DIG)
#else
	#ifdef DECIMAL_DIG
		#define OP_DBL_Digs (DECIMAL_DIG)
	#else
		#define OP_DBL_Digs (DBL_DIG + 3)
	#endif
#endif

const char* CMD_OPTION = "--full-precision";


/**
 * print_usage
 */
static void print_usage (char *progname)
{
	printf ("\nUsage : %s  <input file> [%s] \n", progname, CMD_OPTION) ;

} // print_usage


/**
 * convert_to_text
 */
static void convert_to_text (SNDFILE * infile, FILE * outfile, int channels, int full_precision)
{
	float buf [BLOCK_SIZE] ;
	sf_count_t frames ;
	int k, m, readcount ;

	frames = BLOCK_SIZE / channels ;

	while ((readcount = sf_readf_float (infile, buf, frames)) > 0)
	{
		for (k = 0 ; k < readcount ; k++)
		{	for (m = 0 ; m < channels ; m++) {
				if (full_precision){
					fprintf (outfile, " %.*e", OP_DBL_Digs - 1, buf [k * channels + m]) ;
				} else{
					fprintf (outfile, " % 12.10f", buf [k * channels + m]) ;
				}
				fprintf (outfile, "\n") ;
			} // for
		} // for
	} // while

	return ;
} // convert_to_text


/**
 * main
 */
int
main (int argc, char **argv)
{
	SNDFILE		*infile = NULL ;
	FILE		*outfile = NULL ;
	SF_INFO		sfinfo ;
	int		full_precision = 0 ;

	char* progname = strrchr (argv [0], '/') ;
	progname = progname ? progname + 1 : argv [0] ;

if(argc == 3){
			printf("argv2: %s \n", argv[2]);
			string argv2 = argv[2];
			if( argv2.compare(CMD_OPTION) == 0){
				full_precision = 1 ;
				printf("match \n");
			} else {
				printf("unmatch \n");	
				print_usage (progname) ;
				return 1 ;
			}
}else if(argc != 2){
			print_usage (progname) ;
			return 1 ;
}


	char* infilename = argv [1] ;

	string fname = getFileNameWithExt(infilename);
	string outfilepath =  fname + ".txt";
	char* outfilename = (char*)outfilepath.c_str();

	if (strcmp (infilename, outfilename) == 0) {
		printf ("Error : Input and output filenames are the same.\n\n") ;
		print_usage (progname) ;
		return 1 ;
	}

	if (infilename [0] == '-') {
		printf ("Error : Input filename (%s) looks like an option.\n\n", infilename) ;
		print_usage (progname) ;
		return 1 ;
	}

	if (outfilename [0] == '-') {
		printf ("Error : Output filename (%s) looks like an option.\n\n", outfilename) ;
		print_usage (progname) ;
		return 1 ;
	}

	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	if ((infile = sf_open (infilename, SFM_READ, &sfinfo)) == NULL) {
		printf ("Not able to open input file %s.\n", infilename) ;
		puts (sf_strerror (NULL)) ;
		return 1 ;
	}

	/* Open the output file. */
	if ((outfile = fopen (outfilename, "w")) == NULL) {
		printf ("Not able to open output file %s : %s\n", outfilename, sf_strerror (NULL)) ;
		return 1 ;
	}

	fprintf (outfile, "# Converted from file %s.\n", infilename) ;
	fprintf (outfile, "# Channels %d, Sample rate %d\n", sfinfo.channels, sfinfo.samplerate) ;

	convert_to_text (infile, outfile, sfinfo.channels, full_precision) ;

	sf_close (infile) ;
	fclose (outfile) ;
	printf("converted: %s \n", outfilename);

	return 0 ;
} // main
