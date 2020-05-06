/**
 * libflac Sample
 * 2020-03-01 K.OHWADA
 */

// encode flac from wav
// original : https://github.com/xiph/flac/tree/master/examples

/* example_cpp_encode_file - Simple FLAC file encoder using libFLAC
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
 * This example shows how to use libFLAC++ to encode a WAVE file to a FLAC
 * file.  It only supports 16-bit stereo files in canonical WAVE format.
 *
 * Complete API documentation can be found at:
 *   http://xiph.org/flac/api/
 */


#include "FLAC++/metadata.h"
#include "FLAC++/encoder.h"

#include <string> 
#include<iostream>

#include "wav_header.h"

#include "parse_filename.hpp"


using namespace std;

#define READSIZE 1024


/**
 * class OurEncoder
 */
class OurEncoder: public FLAC::Encoder::File {
public:
	OurEncoder(): FLAC::Encoder::File() { }
protected:
	virtual void progress_callback(FLAC__uint64 bytes_written, FLAC__uint64 samples_written, uint32_t frames_written, uint32_t total_frames_estimate);
};


// global
static uint32_t total_samples = 0; /* can use a 32-bit number due to WAVE size limitations */
static FLAC__byte buffer[READSIZE/*samples*/ * 2/*bytes_per_sample*/ * 2/*channels*/]; /* we read the WAVE data into here */
static FLAC__int32 pcm[READSIZE/*samples*/ * 2/*channels*/];



/**
 * main
 */
int main(int argc, char **argv)
{

    const int COMPRESSION_LEVEL = 5;
    const int PADDING_LEN = 1234; // padding length 

    const char* KEY_ARTIST = "ARTIST";
    const char* VAL_ARTIST = "Some Artist";
    const char* KEY_YEAR = "YEAR";
    const char* VAL_YEAR = "1984";

	OurEncoder encoder;

	FLAC__StreamEncoderInitStatus init_status;
	FLAC__StreamMetadata *metadata[2];
	FLAC__StreamMetadata_VorbisComment_Entry entry;

	bool ok = true;


    if (argc != 2) {
        cout << "Usage: " << argv[0]  << " <wavFile> " << endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];

// output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".flac";
    char* output = (char*)outfile.c_str();

   	FILE *fin = fopen(input, "rb");
	if(!fin) {
        cout << "open Faild: " << input << endl;
        return EXIT_FAILURE;
	}


    // read wav header
    int wavChannels;
    int wavBit;
    int wavSize;
    int wavSamplingrate;
    int ret1 = readWavHeader(fin, &wavChannels, &wavBit, &wavSize, &wavSamplingrate);
	if (ret1 != 0){
        cout << "NOT wav format" << endl;
        fclose(fin);
        return EXIT_FAILURE;
	}

    // wav info
    cout << "wavChannels: " << wavChannels << endl;
    cout << "wavSamplingrate: " << wavSamplingrate << endl;
    cout << "wavBit: " << wavBit << endl;
    cout << "wavSize: " << wavSize << endl;

    total_samples = wavSize;

	// check the encoder 
	if(!encoder) {
        cout << "ERROR: allocating encoder" << endl;
		fclose(fin);
        return EXIT_FAILURE;
	}

	ok &= encoder.set_verify(true);
	ok &= encoder.set_compression_level(COMPRESSION_LEVEL);
	ok &= encoder.set_channels(wavChannels);
	ok &= encoder.set_bits_per_sample(wavBit);
	ok &= encoder.set_sample_rate(wavSamplingrate);
	ok &= encoder.set_total_samples_estimate(wavSize);



	/* now add some metadata; we'll add some tags and a padding block */
	if(ok) {
		if(
			(metadata[0] = FLAC__metadata_object_new(FLAC__METADATA_TYPE_VORBIS_COMMENT)) == NULL ||
			(metadata[1] = FLAC__metadata_object_new(FLAC__METADATA_TYPE_PADDING)) == NULL ||
			/* there are many tag (vorbiscomment) functions but these are convenient for this particular use: */
			!FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(&entry, KEY_ARTIST, VAL_ARTIST) ||
			!FLAC__metadata_object_vorbiscomment_append_comment(metadata[0], entry, /*copy=*/false) || /* copy=false: let metadata object take control of entry's allocated string */
			!FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(&entry, KEY_YEAR, VAL_YEAR) ||
			!FLAC__metadata_object_vorbiscomment_append_comment(metadata[0], entry, /*copy=*/false)
		) {
            cout << "ERROR: out of memory or tag error" << endl;
			ok = false;
		}

		metadata[1]->length = PADDING_LEN; /* set the padding length */

		ok = encoder.set_metadata(metadata, 2);
	}

	/* initialize encoder */
	if(ok) {
		init_status = encoder.init(output);
		if(init_status != FLAC__STREAM_ENCODER_INIT_STATUS_OK) {
            cout << "ERROR: initializing encoder: " << 
                FLAC__StreamEncoderInitStatusString[init_status] << endl;
			ok = false;
		}
	}

	/* read blocks of samples from WAVE file and feed to encoder */
	if(ok) {
		size_t left = (size_t)wavSize;

		while(ok && left) {
			size_t need = (left>READSIZE? (size_t)READSIZE : (size_t)left);
			if(fread(buffer, wavChannels*(wavBit/8), need, fin) != need) {
                cout << "ERROR: reading from WAVE file" << endl;
				ok = false;
			}
			else {
				/* convert the packed little-endian 16-bit PCM samples from WAVE into an interleaved FLAC__int32 buffer for libFLAC */
				size_t i;
				for(i = 0; i < need*wavChannels; i++) {
					/* inefficient but simple and works on big- or little-endian machines */
					pcm[i] = (FLAC__int32)(((FLAC__int16)(FLAC__int8)buffer[2*i+1] << 8) | (FLAC__int16)buffer[2*i]);
				} // for

				/* feed samples to encoder */
				ok = encoder.process_interleaved(pcm, need);
			}
			left -= need;
		} // while

	}

	ok &= encoder.finish();

    cout << "encoding: " << (ok? "succeeded" : "FAILED") << endl;
    cout << " state: " << 
        encoder.get_state().resolved_as_cstring(encoder) << endl;

	/* now that encoding is finished, the metadata can be freed */
	FLAC__metadata_object_delete(metadata[0]);
	FLAC__metadata_object_delete(metadata[1]);

	fclose(fin);

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}


/**
 * progress_callback
 */
void OurEncoder::progress_callback(FLAC__uint64 bytes_written, FLAC__uint64 samples_written, uint32_t frames_written, uint32_t total_frames_estimate)
{
	fprintf(stderr, "wrote %llu bytes, %llu /%u samples, %u/%u frames\n", bytes_written, samples_written, total_samples, frames_written, total_frames_estimate);
}
