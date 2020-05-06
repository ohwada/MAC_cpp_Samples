/**
 * libflac Sample
 * 2020-03-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "FLAC/stream_decoder.h"


#ifndef __FLAC_REDER_H__
#define __FLAC_REDER_H__


#define FLAC_READER_SAMPLINGRATE 44100
#define FLAC_READER_CHANNELS_STREO 2
#define FLAC_READER_CONTINUE 0
#define FLAC_READER_FIRST 1
#define FLAC_READER_ABORT 2


/**
 * class FlacReader
 */
class FlacReader {


public:
    FlacReader(void);
    ~FlacReader(void);
    int open(char *filename, 
        FLAC__StreamDecoderWriteCallback write_callback,
		FLAC__StreamDecoderMetadataCallback metadata_callback,
        FLAC__StreamDecoderErrorCallback error_callback );
    void close(void);

    int proc_write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data);
    void proc_metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data);
    void proc_error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data);

    unsigned char* getPcmData(void);
    int getPcmDataSize(void);

    bool end_of_stream(void);

    int getFileSize( char* filename);
    int getSampleRate(void);
    int getChannels(void);
    int getBps(void);
    int getTotalSize(void);

    void printProgess(void);
    void printResult(bool ok);

    int FRAMES_PER_SEC;

private:
    char * getState(void);

	FILE *m_fp;
    unsigned char *m_buffer;

	FLAC__StreamDecoder *m_decoder;

    int m_buffer_size;
    int m_sample_number;
    int m_frame_count;
    int m_total_pcm_size;
    int m_total_frames;
    int m_total_samples ;
    int m_sample_rate ;
    int m_channels ;
    int m_bps ;

};


#endif /* FLAC_REDER_H */

