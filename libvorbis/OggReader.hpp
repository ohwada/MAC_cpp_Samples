/**
 * libvorbis Sample
 * 2020-03-01 K.OHWADA
 */

#include <string>
#include <iostream>

#include "vorbis/vorbisfile.h"


#ifndef __OGG_REDER_H__
#define __OGG_REDER_H__

#define OGG_READER_SAMPLINGRATE 44100
#define OGG_READER_CHANNELS_STEREO 2
#define OGG_READER_BUFF_SIZE 4096
#define OGG_READER_CONTINUE 0
#define OGG_READER_END 1


/**
 * class OggReader
 */
class OggReader
{
public:
    OggReader(void);
    ~OggReader(void);
    int open(char *filename);
    void close(void);
    int read(void);
    char* getBuffer(void);
    void printFileInfo(void);
    void printOvInfo(void);
    void printPregress(void);

    float FRAMES_PER_SEC;

private:
    FILE *m_fp;
    OggVorbis_File m_ovf;
    char *m_ov_buffer;
    int m_total;
    int m_total_frames;
    int m_read_size;

    int m_frame_count;
    int m_ov_version;
    int m_ov_channels;
    long m_ov_rate;

};


#endif /* OGG_REDER_H_H */
