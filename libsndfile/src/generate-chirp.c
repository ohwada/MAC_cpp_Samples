/**
 * libsndfile sample
 * 2020-03-01 K.OHWADA
 */

// Create a sound file containing a swept sine wave
// reference : http://www.mega-nerd.com/libsndfile/tools/#generate-chirp

/*
** Copyright (C) 2007-2015 Erik de Castro Lopo <erikd@mega-nerd.com>
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

/* Generate a sound file containing a chirp */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "common.h"

#include <sndfile.h>

typedef double (*freq_func_t) (double w0, double w1, double total_length) ;

typedef struct
{	double amplitude ;
	int samplerate, format ;
	double start_freq, end_freq, seconds ;
	freq_func_t sweep_func ;
} PARAMS ;


// prototype
static void usage (const char * argv0) ;
static void check_int_range (const char * name, int value, int lower, int upper) ;
static void check_double_range (const char * name, double value, double lower, double upper) ;
static freq_func_t parse_sweep_type (const char * name) ;
static int guess_major_format (const char * filename) ;
static void generate_file (const char * filename, const PARAMS * params) ;


/**
 * main
 */
int main (int argc, char ** argv)
{

	const int SAMPLERATE = 44100;
	const double SECONDS = 2.0;
	const double START_FREQ = 200.0;
 	const double END_FREQ = SAMPLERATE/2;

	PARAMS params = { 1.0, -1, -1, 0, 0, 0, NULL } ;

	params.samplerate = SAMPLERATE;
	params.seconds = SECONDS;
	params.start_freq = START_FREQ;
	params.end_freq = END_FREQ;

	const char * filename;

	if(argc == 1){
		usage(argv [0]) ;
	}

	int k ;
	for (k = 1 ; k < argc -3; k++)
	{
		if (strcmp (argv [k], "-from") == 0)
		{	k++ ;
			params.start_freq = parse_double_or_die (argv [k], "from frequency") ;
			continue ;
		}

		if (strcmp (argv [k], "-to") == 0)
		{	k++ ;
			params.end_freq = parse_double_or_die (argv [k], "to frequency") ;
			continue ;
		}

		if (strcmp (argv [k], "-amp") == 0)
		{	k++ ;
			params.amplitude = strtod (argv [k], NULL) ;
			continue ;
		}

		if (argv [k][0] == '-')
		{	params.sweep_func = parse_sweep_type (argv [k]) ;
			continue ;
		}

		printf ("\nUnknow option '%s'.\n\n", argv [k]) ;
		exit (1) ;

	} // for


	if(argc > 3){
		params.samplerate = parse_int_or_die (argv [argc - 3], "sample rate") ;
	}

	printf("samplerate: %d \n", params.samplerate);

	if(argc > 2){
		params.seconds = parse_double_or_die (argv [argc - 2], "seconds") ;
	}

	printf("seconds: %f \n", params.seconds);

	char output[100] ;
	sprintf(output, "chirp_%d_%d_%d_%d.wav", 
		(int)params.start_freq,
		(int)params.end_freq,
		params.samplerate, 
		(int)params.seconds);

	filename = output;

	if(argc > 1){
		filename = argv [argc - 1] ;
	}

	printf("filename: %s \n", filename);

	check_int_range ("sample rate", params.samplerate, 1000, 200 * 1000) ;
	check_double_range ("seconds", params.seconds, 0.1, 100.0) ;

	if (params.sweep_func == NULL)
		params.sweep_func = parse_sweep_type ("-log") ;
	if (params.start_freq <= 0.0)
		params.start_freq = 100.0 ;
	if (params.end_freq <= 0.0)
		params.end_freq = params.samplerate / 2.0 - 100.0 ;

	if (params.end_freq <= params.start_freq)
	{	printf ("\nError : end frequency %g < start frequency %g.\n\n", params.end_freq, params.start_freq) ;
		exit (1) ;
		} ;

	params.format = guess_major_format (filename) | SF_FORMAT_FLOAT ;

	generate_file (filename, &params) ;

	printf("created: %s \n", filename);
	return 0 ;
} // main 


/**
 * usage
 */
// static void usage_exit(const char * argv0)
static void usage(const char * argv0)
{
	const char * progname ;

	progname = strrchr (argv0, '/') ;
	progname = (progname == NULL) ? argv0 : progname + 1 ;

	puts ("\nCreate a sound file containing a swept sine wave (ie a chirp).") ;

	printf ("\nUsage :\n\n    %s  [options] <sample rate> <length in seconds> <sound file>\n\n", progname) ;

	puts (
		"    Options include:\n\n"
		"        -from <start>    Sweep start frequency in Hz (default 200Hz).\n"
		"        -to <end>        Sweep end frequency in Hz (default fs/2).\n"
		"        -amp <value>     Amplitude of generated sine (default 1.0).\n"
		"        <sweep type>     One of (default -log):\n"
		"                             -log     logarithmic sweep\n"
		"                             -quad    quadratic sweep\n"
		"                             -linear  linear sweep\n"
		"\n"
		"        The <lengths in seconds> parameter can be a decimal like 1.5.\n"
		) ;

	puts (
		"    The output file will contain floating point samples in the range [-1.0, 1.0].\n"
		"    The output file type is determined by the file name extension which should be one\n"
		"    of 'wav', 'aifc', 'aif', 'aiff', 'au', 'caf' and 'w64'.\n"
		) ;

	//exit (0) ;
} // usage


/**
 * check_int_range
 */
static void check_int_range (const char * name, int value, int lower, int upper)
{
	if (value < lower || value > upper)
	{	printf ("Error : '%s' parameter must be in range [%d, %d]\n", name, lower, upper) ;
		exit (1) ;
		} ;
} // check_int_range 


/**
 * check_double_range
 */
static void check_double_range (const char * name, double value, double lower, double upper)
{
	if (value < lower || value > upper)
	{	printf ("Error : '%s' parameter must be in range [%.1f, %.1f]\n", name, lower, upper) ;
		exit (1) ;
	}
} // check_double_range


/**
 * write_chirp
 */
static void write_chirp (SNDFILE * file, int samplerate, double seconds, double amp, double w0, double w1, freq_func_t sweep_func)
{
	double instantaneous_w, current_phase ;
	float * data ;
	int total_samples, k ;

	total_samples = lrint (seconds * samplerate) ;

	data = malloc (total_samples * sizeof (data [0])) ;
	if (data == NULL)
	{	printf ("\nError : malloc failed : %s\n", strerror (errno)) ;
		exit (1) ;
		} ;

	current_phase = 0.0 ;
	instantaneous_w = w0 ;

	printf ("Start frequency : %8.1f Hz (%f rad/sec)\n", instantaneous_w * samplerate / (2.0 * M_PI), instantaneous_w) ;

	for (k = 0 ; k < total_samples ; k++)
	{	data [k] = amp * sin (current_phase) ;

		instantaneous_w = sweep_func (w0, w1, (1.0 * k) / total_samples) ;
		current_phase = fmod (current_phase + instantaneous_w, 2.0 * M_PI) ;

		} ;

	sf_write_float (file, data, total_samples) ;

	printf ("End   frequency : %8.1f Hz (%f rad/sec)\n", instantaneous_w * samplerate / (2.0 * M_PI), instantaneous_w) ;

	free (data) ;
} // write_chirp 


/**
 * generate_file
 */
static void generate_file (const char * filename, const PARAMS * params)
{
	char buffer [1024] ;
	SNDFILE * file ;
	SF_INFO info ;
	double w0, w1 ;

	memset (&info, 0, sizeof (info)) ;

	info.format = params->format ;
	info.samplerate = params->samplerate ;
	info.channels = 1 ;

	file = sf_open (filename, SFM_WRITE, &info) ;
	if (file == NULL)
	{	printf ("\nError : Not able to create file named '%s' : %s/\n", filename, sf_strerror (NULL)) ;
		exit (1) ;
		} ;

	sf_set_string (file, SF_STR_TITLE, "Logarithmic chirp signal") ;

	snprintf (buffer, sizeof (buffer), "start_freq : %g Hz   end_freq : %g Hz   amplitude : %g", params->start_freq, params->end_freq, params->amplitude) ;
	sf_set_string (file, SF_STR_COMMENT, buffer) ;

	sf_set_string (file, SF_STR_SOFTWARE, "sndfile-generate-chirp") ;
	sf_set_string (file, SF_STR_COPYRIGHT, "No copyright.") ;

	w0 = 2.0 * M_PI * params->start_freq / params->samplerate ;
	w1 = 2.0 * M_PI * params->end_freq / params->samplerate ;

	write_chirp (file, params->samplerate, params->seconds, params->amplitude, w0, w1, params->sweep_func) ;

	sf_close (file) ;
} // generate_file 


/**
 * log_freq_func
 */
static double log_freq_func (double w0, double w1, double indx)
{
	return pow (10.0, log10 (w0) + (log10 (w1) - log10 (w0)) * indx) ;
} // log_freq_func 


/**
 * quad_freq_func
 */
static double
quad_freq_func (double w0, double w1, double indx)
{	return w0 + (w1 - w0) * indx * indx ;
} // log_freq_func 


/**
 * linear_freq_func
 */
static double linear_freq_func (double w0, double w1, double indx)
{
	return w0 + (w1 - w0) * indx ;
} // linear_freq_func 


/**
 * parse_sweep_type
 */
static freq_func_t parse_sweep_type (const char * name)
{
	if (strcmp (name, "-log") == 0)
		return log_freq_func ;
	if (strcmp (name, "-quad") == 0)
		return quad_freq_func ;
	if (strcmp (name, "-linear") == 0)
		return linear_freq_func ;

	printf ("\nError : Bad sweep type. Should be one of '-log', '-quad' and '-linear'.\n\n") ;
	exit (1) ;
	return NULL ;
} // parse_sweep_type


/**
 * guess_major_format
 */
static int guess_major_format (const char * filename)
{
	const char * ext ;

	ext = strrchr (filename, '.') ;
	if (ext == NULL)
	{	printf ("\nError : cannot figure out file type from file name '%s'.\n\n", filename) ;
		exit (1) ;
		} ;

	if (strcasecmp (ext, ".wav") == 0)
		return SF_FORMAT_WAV ;
	if (strcasecmp (ext, ".aif") == 0 || strcasecmp (ext, ".aiff") == 0 || strcasecmp (ext, ".aifc") == 0)
		return SF_FORMAT_AIFF ;
	if (strcasecmp (ext, ".au") == 0)
		return SF_FORMAT_AU ;
	if (strcasecmp (ext, ".caf") == 0)
		return SF_FORMAT_CAF ;
	if (strcasecmp (ext, ".w64") == 0)
		return SF_FORMAT_W64 ;

	printf ("\nError : Can only generate files with extentions 'wav', 'aifc', 'aiff', 'aif', 'au', 'w64' and 'caf'.\n\n") ;
	exit (1) ;
	return 0 ;
} // guess_major_format

