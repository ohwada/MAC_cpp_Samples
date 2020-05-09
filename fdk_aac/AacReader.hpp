/**
 * fdk aac Sample
 * 2020-03-01 K.OHWADA
 */

// aac decoder
// original : https://github.com/akanchi/aac-example

#ifndef FDKAAC_DEC_H
#define FDKAAC_DEC_H


 #include <stdlib.h>
 #include <stdio.h>
 #include <stdio.h>
#include <sys/stat.h>

#include "fdk-aac/aacdecoder_lib.h"


#define AAC_READER_SAMPLINGRATE 44100
#define AAC_READER__SUCCESS 0
#define AAC_READER_CONTINUE 1
#define AAC_READER_END 2


/**
 * class adts_header_t
 */
class adts_header_t
{
public:
	unsigned char syncword_0_to_8						: 	8;

	unsigned char protection_absent						:	1;
	unsigned char layer									: 	2;
	unsigned char ID 									:	1;
	unsigned char syncword_9_to_12						:	4;

	unsigned char channel_configuration_0_bit			:	1;
	unsigned char private_bit							:	1;
	unsigned char sampling_frequency_index				:	4;
	unsigned char profile								:	2;

	unsigned char frame_length_0_to_1 					: 	2;
	unsigned char copyrignt_identification_start		: 	1;
	unsigned char copyright_identification_bit 			: 	1;
	unsigned char home 									: 	1;
	unsigned char original_or_copy 						: 	1;
	unsigned char channel_configuration_1_to_2 			: 	2;

	unsigned char frame_length_2_to_9					:	8;

	unsigned char adts_buffer_fullness_0_to_4 			: 	5;
	unsigned char frame_length_10_to_12 				: 	3;

	unsigned char number_of_raw_data_blocks_in_frame 	: 	2;
	unsigned char adts_buffer_fullness_5_to_10 			: 	6;
};


/**
 * class aacdec_t
 */
class aacdec_t
{
public:
	// the decoder handler.
	HANDLE_AACDECODER dec;
	// whether use ADTS mode.
	int is_adts;
	// init until the first frame decoded.
	CStreamInfo *info;
	// the bits of sample, always 16 for fdkaac.
	int sample_bits;
	// total filled bytes.
	unsigned int filled_bytes;
};


/**
 * class AacReader
 */
class AacReader
{
public:
	AacReader();
	~AacReader();

	int  readFile(char *filename);
	int decodeAac(void);
	void freeBuffer(void);
	int open(char *filename);
	void close(void);

	char* getPcmData(void);
	int getPcmDataSize(void);

	int getSampleRate(void);
	int getChannels(void);
	int getFrameSize(void);

	void printFileInfo(void);
	void printDecodeInfo(void);
	void printFrameInfo(void);
	void printPregress(void);

	float FRAMES_PER_SEC;

private:
	int aacdec_init_adts();
	void aacdec_close();
	int aacdec_fill(char *data, int nb_data, int *pnb_left);
	int aacdec_sample_bits();
	int aacdec_pcm_size();
	int aacdec_decode_frame(char *pcm, int nb_pcm, int *pnb_valid);

	int aacdec_sample_rate();
	int aacdec_frame_size();
	int aacdec_num_channels();
	int aacdec_aac_sample_rate();
	int aacdec_profile();
	int aacdec_audio_object_type();
	int aacdec_channel_config();
	int aacdec_bitrate();
	int aacdec_aac_samples_per_frame();
	int aacdec_aac_num_channels();
	int aacdec_extension_audio_object_type();
	int aacdec_extension_sampling_rate();
	int aacdec_num_lost_access_units();
	int aacdec_num_total_bytes();
	int aacdec_num_bad_bytes();
	int aacdec_num_total_access_units();
	int aacdec_num_bad_access_units();

	FILE *m_fp;

	aacdec_t  m_aacdec;

	adts_header_t m_adts_header;
	//std::ifstream m_in_stream_aac;

	char *m_pcm_buffer;
	char *m_aac_buffer;

	int m_num_pcm;
	int m_aac_size;
    int m_pos;
	int m_pcm_buffer_valid_size;	
	int m_frame_count;
	int m_sum_pcm_size;
	int m_file_size;
	int m_total_frames;
    bool m_is_first;

};

#endif
