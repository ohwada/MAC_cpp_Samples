/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <mad.h>


#ifndef __MP3_H__
#define __MP3_H__

#define MP3_SAMPLINGRATE 44100
#define MP3_CHANNELS_STEREO 2
#define MP3_DECODE_SUCCESS 0
#define MP3_DECODE_SKIP 1
#define MP3_DECODE_END 2


/**
 * class MP3Reader
 */
class MP3Reader
{
public:
    MP3Reader(void);
    ~MP3Reader(void);
    int open(char* filename);
    void close(void);

    int decode(void);
    unsigned char* getFrameData(void);
    int getFrameDataSize(void);

    void printFileInfo(void);
    void printFrameInfo(void);
    void printPregress(void);
    void printDecodedInfo(void);

    int FRAME_BUFF_SIZE;
    int FRAMES_PER_SEC;

private:
    void setFrameBuffer(struct mad_pcm *pcm);
    int scale(mad_fixed_t sample);
    char* getStrError(enum mad_error error);

    FILE *m_fp;
    int m_file_size;
    int m_total_frames;

    struct mad_stream m_mad_stream;
    struct mad_frame m_mad_frame;
    struct mad_synth m_mad_synth;
	mad_timer_t  m_mad_timer;

    unsigned char *m_frame_buffer;
	int m_frame_count;
    int m_frame_length;
    int m_frame_channels;
    int m_frame_samplerate;
    bool m_is_first;
};

#endif /* MP3_H */