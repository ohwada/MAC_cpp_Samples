/**
 * libsndfile sample
 * 2020-03-01 K.OHWADA
 */

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

// #include "config.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#include "common.h"

/* Global. */
const char *font_family = "DejaVu Sans Mono" ;

sf_count_t
sfx_mix_mono_read_double (SNDFILE * file, double * data, sf_count_t datalen)
{
	SF_INFO info ;

	sf_command (file, SFC_GET_CURRENT_SF_INFO, &info, sizeof (info)) ;

	if (info.channels == 1)
		return sf_read_double (file, data, datalen) ;

	static double multi_data [2048] ;
	int k, ch, frames_read ;
	sf_count_t dataout = 0 ;

	while (dataout < datalen)
	{	int this_read ;

		this_read = MIN (ARRAY_LEN (multi_data) / info.channels, datalen - dataout) ;

		frames_read = sf_readf_double (file, multi_data, this_read) ;
		if (frames_read == 0)
			break ;

		for (k = 0 ; k < frames_read ; k++)
		{	double mix = 0.0 ;

			for (ch = 0 ; ch < info.channels ; ch++)
				mix += multi_data [k * info.channels + ch] ;
			data [dataout + k] = mix / info.channels ;
			} ;

		dataout += frames_read ;
		} ;

	return dataout ;
} /* sfx_mix_mono_read_double */

int
parse_int_or_die (const char * input, const char * value_name)
{	char * endptr ;

	long value = strtol (input, &endptr, 10) ;

	if (endptr == input || endptr [0] != 0 || value >= INT_MAX)
	{	fprintf (stderr, "Error : Can't parse int value %s : %s\n", value_name, input) ;
		exit (1) ;
		} ;

	return value ;
} /* parse_int_or_die */

double
parse_double_or_die (const char * input, const char * value_name)
{	char * endptr ;

	double value = strtod (input, &endptr) ;

	if (endptr == input || endptr [0] != 0)
	{	fprintf (stderr, "Error : Can't parse double value %s : %s\n", value_name, input) ;
		exit (1) ;
		} ;

	return value ;
} /* parse_double_or_die */
