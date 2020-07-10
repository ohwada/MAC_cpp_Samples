/**
 * flac Sample
 * 2020-03-01 K.OHWADA
 */


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


#include "FlacReader.hpp"


// global
const int BLOCK_SIZE = 4096;
const int BUF_SIZE = 4 * BLOCK_SIZE;
const int STREAM_BPS_16 = 16;


/**
 * constractor
 */
FlacReader::FlacReader(void)
{
    m_buffer = new unsigned char[BUF_SIZE];

    FRAMES_PER_SEC = (float)FLAC_READER_SAMPLINGRATE / (float)(BLOCK_SIZE) ;

    m_buffer_size = 0;
    m_sample_number = 0;
    m_total_samples = 0 ;
    m_sample_rate = 0 ;
    m_channels = 0;
    m_bps = 0;
    m_frame_count = 0;
}


/**
 * destractor
 */
FlacReader::~FlacReader(void)
{
    delete [] m_buffer;
}



/**
 * open
 */
int FlacReader::open(char *filename, 
        FLAC__StreamDecoderWriteCallback write_callback,
		FLAC__StreamDecoderMetadataCallback metadata_callback, 
        FLAC__StreamDecoderErrorCallback error_callback)
{

    m_decoder = FLAC__stream_decoder_new();
	if(!m_decoder) {
		return 1;
	}

	(void)FLAC__stream_decoder_set_md5_checking(m_decoder, true);
	
    FLAC__StreamDecoderInitStatus init_status = FLAC__stream_decoder_init_file(m_decoder, filename, write_callback, metadata_callback, error_callback, /*client_data=*/ NULL);

	if(init_status != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        return 2;
	}

	return 0;
}


/**
 * close
 */
void FlacReader::close(void)
{
	FLAC__stream_decoder_delete(m_decoder);
	fclose(m_fp);
}


/**
 * end_of_stream
 */
bool FlacReader::end_of_stream(void)
{
	FLAC__bool ret = FLAC__stream_decoder_process_until_end_of_stream(m_decoder);

	return (bool)ret;
}


/**
 * proc_write_callback
 */
int FlacReader::proc_write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
{

    m_frame_count ++;
	m_sample_number = frame->header.number.sample_number;

    m_total_pcm_size = (int)(m_total_samples * m_channels * (m_bps/8));

	if(m_total_samples == 0) {
printf("no samples \n");
		return FLAC_READER_ABORT;
	}

	if(m_channels != FLAC_READER_CHANNELS_STREO ) {
printf("not stereno \n");
		return FLAC_READER_ABORT;
	}

	if(m_bps != STREAM_BPS_16) {
printf("not 16 bit \n");
		return FLAC_READER_ABORT;
	}

	if(buffer [0] == NULL) {
        printf("no left ch \n");
		return FLAC_READER_ABORT;
	}

	if(buffer [1] == NULL) {
        printf("no righ ch \n");
		return FLAC_READER_ABORT;
	}

    // blocksize
    int blocksize = frame->header.blocksize;
    if(blocksize > BLOCK_SIZE){
        printf(" big blocksize  \n");
		return FLAC_READER_ABORT;
    }else if(blocksize > BLOCK_SIZE){
        printf(" blocksize: %d \n", blocksize);
    }

    // set buffer
	for(int i = 0; i < blocksize; i++) {
        int index = 4 * i;
        FLAC__int16 left = (FLAC__int16)buffer[0][i];
        FLAC__int16 right = (FLAC__int16)buffer[1][i];
        m_buffer[index + 0] = left;
        m_buffer[index + 1] = (left >> 8);
        m_buffer[index + 2] = right;
        m_buffer[index + 3] = (right >> 8);
    } // for

    m_buffer_size = 4 * blocksize;
	if(m_sample_number == 0) {
		return FLAC_READER_FIRST;
	}

	return FLAC_READER_CONTINUE;
}



/**
 * proc_metadata_callback
 */
void FlacReader::proc_metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
{

	/* print some stats */
	if(metadata->type == FLAC__METADATA_TYPE_STREAMINFO) {
		/* save for later */
		m_total_samples = metadata->data.stream_info.total_samples;
		m_sample_rate = metadata->data.stream_info.sample_rate;
		m_channels = metadata->data.stream_info.channels;
		m_bps = metadata->data.stream_info.bits_per_sample;

		fprintf(stderr, "sample rate    : %d Hz\n", m_sample_rate);
		fprintf(stderr, "channels       : %d \n", m_channels);
		fprintf(stderr, "bits per sample: %d \n", m_bps);
		fprintf(stderr, "total samples  : %d \n", m_total_samples);
	}

}

/**
 * proc_error_callback
 */
void FlacReader::proc_error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
{
	fprintf(stderr, "Got error callback: %s\n", FLAC__StreamDecoderErrorStatusString[status]);
}

/**
 * getPcmData
 */
unsigned char* FlacReader::getPcmData(void)
{
	return m_buffer;
}


/**
 * getPcmDataSize
 */
int FlacReader::getPcmDataSize(void)
{
	return m_buffer_size;
}


/**
 * getSampleRate
 */
int FlacReader::getSampleRate(void)
{
	return m_sample_rate;
}


/**
 * getChannels
 */
int FlacReader::getChannels(void)
{
	return m_channels;
}


/**
 * getBps
 */
int FlacReader::getBps(void)
{
	return m_bps;
}


/**
 * getTotalSize
 */
int FlacReader::getTotalSize(void)
{
    return m_total_samples;
}


/**
 * getFileSize
 */
int FlacReader::getFileSize( char* filename)
{

    // File pointer
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return 0;
    }

    // Fetch file size, etc
    struct stat file_stat;
    int fd = fileno(fp);
    int ret = fstat(fd, & file_stat);

    fclose(fp);

    if (ret != 0) {
        return 0;
    }

    return (int)file_stat.st_size;
}


/**
 * printProgess
 */
void FlacReader::printProgess(void)
{
        int total_frames = m_total_samples / BLOCK_SIZE;
        int playback_time = (float)total_frames / FRAMES_PER_SEC ;

        int remain_frames = total_frames -  m_frame_count;
        if(remain_frames < 0){
            remain_frames = 0;
        }

        float remain_sec = (float)remain_frames / FRAMES_PER_SEC;

        if(m_frame_count == 1){
            printf("total pcm size: %d bytes \n", m_total_pcm_size);
            printf("total frames: %d frames \n", total_frames);
            printf("playback: %d sec \n",  playback_time);
        }

        fprintf(stderr, "\r [ %3d / %3d ] ( %3d sec)",  m_frame_count,  total_frames, (int)remain_sec);

}


/**
 * printResult
 */
void FlacReader::printResult(bool ok)
{
		fprintf(stderr, "\n");
		printf("decoding: %s\n", ok? "Succeeded" : "FAILED");
		printf("decoded: %d frames\n", m_frame_count);
		printf("state: %s\n", getState() );
}


/**
 * getState
 */
char * FlacReader::getState(void)
{
	char *state = new char[80];
	state = (char *)FLAC__StreamDecoderStateString[FLAC__stream_decoder_get_state(m_decoder)];
	return state;
}

