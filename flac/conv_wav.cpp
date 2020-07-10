/**
 * flac Sample
 * 2020-03-01 K.OHWADA
 */


// convrt flac to wav
// original : https://github.com/xiph/flac/tree/master/examples

/* example_c_decode_file - Simple FLAC file decoder using libFLAC
 * Copyright (C) 2007-2009  Josh Coalson
 * Copyright (C) 2011-2016  Xiph.Org Foundation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * This example shows how to use libFLAC to decode a FLAC file to a WAVE
 * file.  It only supports 16-bit stereo files.
 *
 * Complete API documentation can be found at:
 *   http://xiph.org/flac/api/
 */


#include <string> 
#include<iostream>


#include "FlacReader.hpp"

#include "wav_header.h"

#include "parse_filename.hpp"

using namespace std;


// prototype
static FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data);
static void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data);
static void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data);

// global
FlacReader  reader;
FILE *fout;
char* output;


/**
 * main
 */
int main(int argc, char **argv)
{

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <flacFile> " <<  endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];

// output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".wav";
    output = (char*)outfile.c_str();


	fout = fopen(output, "wb");
	if(!fout) {
        cout << "fopen Faild: " << output << endl;
        return EXIT_FAILURE;
	}


int ret1 = reader.open(input, 
        write_callback,
        metadata_callback,
        error_callback );

	if(ret1 != 0) {
        cout << "open Faild: " << input << endl;
		return 1;
	}

    bool ok = reader.end_of_stream();
    reader.printResult(ok);

    reader.close();

    cout << "saved:" << output << endl;

    return EXIT_SUCCESS;
}


/**
 * write_callback
 */
FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
{

    int ret1 = reader.proc_write_callback(decoder, frame, buffer, client_data);

    if(ret1 == FLAC_READER_ABORT){
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;;
    }

    if(ret1 == FLAC_READER_FIRST){

        int sample_rate = reader.getSampleRate();
     int channels = reader.getChannels();
        int total_size = reader.getTotalSize();
        bool ret2 = writeWavHeaderFp(fout, channels, sample_rate, total_size);
        if(!ret2){
            cout << "writeWavHeader Faild: " << output << endl;
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
		}
    }

    unsigned char* data = reader.getPcmData();
    int datasize = reader.getPcmDataSize();

    int wsize = fwrite(data, 1, datasize, fout);
    if(wsize != datasize){
            cout << "fwrite Faild: " << output << endl;
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
    }

	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}



/**
 * metadata_callback
 */
void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
{
    reader.proc_metadata_callback(decoder, metadata, client_data);
}


/**
 * error_callback
 */
void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
{
    reader.proc_error_callback( decoder, status, client_data);
}

