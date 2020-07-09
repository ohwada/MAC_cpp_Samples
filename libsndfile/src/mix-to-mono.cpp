/**
 * libsndfile sample
 * 2020-03-01 K.OHWADA
 */


// Convert a multi-channel input file to a mono output file, 
// by mixing all input channels into one.
// reference ; http://www.mega-nerd.com/libsndfile/tools/#mix-to-mono

/*
** Copyright (C) 2007-2011 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 or version 3 of the
** License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common.h"

#include  "parse_filename.hpp"

using namespace std;

// prototype
static void usage_exit (void) ;
static void mix_to_mono (SNDFILE * infile, SNDFILE * outfile) ;


/**
 * createOutFileName
 */
string createOutputFileName(string input )
{
	string fname = getFileNameWithoutExt(input);
	string ext = getFileNameExt(input);
	string outname = fname + "_mono." + ext;
	return outname;
}


/**
 * main
 */
int main (int argc, char ** argv)
{
	SNDFILE *infile, *outfile ;
	SF_INFO sfinfo ;

	char *input;
	char *output;

	if(argc == 3){
		input = argv [1];
		output = argv [2];
	} else if(argc == 2){
		input = argv [1];
		string outname = createOutputFileName(input);
		output = (char *)outname.c_str();
	}else {
		usage_exit () ;
	}

	if (strcmp (input, output) == 0)
	{	printf ("Error : input and output file names are the same.\n") ;
		 return EXIT_FAILURE;
	} 

	/* Delete the output file length to zero if already exists. */
	remove (output) ;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;
	if ((infile = sf_open (input, SFM_READ, &sfinfo)) == NULL)
	{	printf ("Error : Not able to open input file '%s'\n", input) ;
		sf_close (infile) ;
        return EXIT_FAILURE;
	} 

	if (sfinfo.channels == 1)
	{	printf ("Input file '%s' already mono. Exiting.\n", input) ;
		sf_close (infile) ;
        return EXIT_FAILURE;
	} 

	/* Force output channels to mono. */
	sfinfo.channels = 1 ;

	if ((outfile = sf_open (output, SFM_WRITE, &sfinfo)) == NULL)
	{	printf ("Error : Not able to open output file '%s'\n", output) ;
		sf_close (infile) ;
        return EXIT_FAILURE;
	} 

	mix_to_mono (infile, outfile) ;

	sf_close (infile) ;
	sf_close (outfile) ;
	cout << "created: " << output << endl;

	return EXIT_SUCCESS;
} // main 


/**
 * mix_to_mono
 */
static void mix_to_mono (SNDFILE * infile, SNDFILE * outfile)
{	double buffer [1024] ;
	sf_count_t count ;

	while ((count = sfx_mix_mono_read_double (infile, buffer, ARRAY_LEN (buffer))) > 0)
		sf_write_double (outfile, buffer, count) ;

	return ;
} // mix_to_mono 


 /**
 * usage_exit
 */
static void
usage_exit (void)
{
	puts ("\n"
		"Usage :\n\n"
		"    sndfile-mix-to-mono <input file> [output file] \n"
		) ;
	exit (0) ;
} // usage_exit 
