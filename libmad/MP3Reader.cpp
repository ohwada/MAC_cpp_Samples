/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */


// reference : https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html


 #include "MP3Reader.hpp"

using namespace std;


// global
const int FRAME_LENGTH = 1152;


/**
 * constractor
 */
MP3Reader::MP3Reader(void)
{
    FRAME_BUFF_SIZE  = 4 * FRAME_LENGTH;
    m_frame_buffer = new unsigned char[FRAME_BUFF_SIZE];

    FRAMES_PER_SEC = (float)MP3_SAMPLINGRATE / (float )FRAME_LENGTH ;
	m_frame_count = 0;
    m_is_first = false;
}


/**
 * destractor
 */
MP3Reader::~MP3Reader(void)
{
    delete[] m_frame_buffer;
}


/**
 * open
 */
int MP3Reader::open(char* filename)
{
    // open input file
    m_fp = fopen(filename, "rb");
    if (!m_fp) {
        return 1;
    }

    // fetch file size
    struct stat file_stat;
    int fd = fileno(m_fp);
    int ret = fstat(fd, &file_stat);
    if (ret != 0) {
        fclose(m_fp);
        return 2;
    }

    m_file_size = (int)file_stat.st_size;
    m_total_frames = ( m_file_size / FRAME_LENGTH ) ;

    // Let kernel do all the dirty job of buffering etc, map file contents to memory
    unsigned char *input_stream = (unsigned char *)mmap(0, m_file_size, PROT_READ, MAP_SHARED, fd, 0);
    if(!input_stream){
        return 3;
    }

    // Initialize MAD library
    mad_stream_init(&m_mad_stream);
    mad_synth_init(&m_mad_synth);
    mad_frame_init(&m_mad_frame);

    // Copy pointer and length to m_mad_stream struct
    mad_stream_buffer(&m_mad_stream, input_stream, m_file_size);

    return 0;
}


/**
 * close
 */
void MP3Reader::close()
{
    fclose(m_fp);

    // Free MAD structs
    mad_synth_finish(&m_mad_synth);
    mad_frame_finish(&m_mad_frame);
    mad_stream_finish(&m_mad_stream);
}


/**
 * decode
 */
int MP3Reader::decode(void)
{

        // Decode frame from the stream
        int ret = mad_frame_decode(&m_mad_frame, &m_mad_stream);
        if (ret) {
            enum mad_error stream_error = m_mad_stream.error;
            char* str_error = MP3Reader::getStrError(stream_error);
            if (MAD_RECOVERABLE(stream_error)) {
                printf("recoverable: %s ( %d ) \n", str_error, stream_error);
                return MP3_DECODE_SKIP;
            } else if (stream_error == MAD_ERROR_BUFLEN) {
                printf("error buflen \n");
                return MP3_DECODE_SKIP;
            } else {
                printf("error: %s ( %d ) \n", str_error, stream_error);
                return MP3_DECODE_END;
            }
        }

		m_frame_count++;
		mad_timer_add(&m_mad_timer, m_mad_frame.header.duration);

        // Synthesize PCM data of frame
        mad_synth_frame(&m_mad_synth, &m_mad_frame);

    struct mad_pcm *pcm = &m_mad_synth.pcm;
    m_frame_samplerate = pcm->samplerate;
    m_frame_length = pcm->length;
    m_frame_channels = pcm->channels;

    if(m_frame_length != FRAME_LENGTH) {
        printf("error frame length : %d \n", m_frame_length);
        return MP3_DECODE_SKIP; 
    }else if(m_frame_samplerate != MP3_SAMPLINGRATE) {
        printf("error samplerate: %d \n", m_frame_samplerate);
        return MP3_DECODE_SKIP; 
    }else if(m_frame_channels != MP3_CHANNELS_STEREO) {
         printf("error not stereo \n");
        return MP3_DECODE_SKIP; 
    }

    setFrameBuffer(pcm);

    if(m_is_first){
        m_is_first = false;
        printFrameInfo();
    }

    if(m_frame_count > (m_total_frames + 10)){
         return MP3_DECODE_END;
    }

         return MP3_DECODE_SUCCESS;
}



/**
 * getFrameData
 */
unsigned char* MP3Reader::getFrameData(void)
{
    return m_frame_buffer;
}


/**
 * getFrameDataSize
 */
int MP3Reader::getFrameDataSize(void)
{
    return FRAME_BUFF_SIZE;
}



/**
 * scale
 */
int MP3Reader::scale(mad_fixed_t sample) {
     /* round */
     sample += (1L << (MAD_F_FRACBITS - 16));
     /* clip */
     if (sample >= MAD_F_ONE)
         sample = MAD_F_ONE - 1;
     else if (sample < -MAD_F_ONE)
         sample = -MAD_F_ONE;
     /* quantize */
     return sample >> (MAD_F_FRACBITS + 1 - 16);
}



/**
 * setFrameBuffer
 */
void MP3Reader::setFrameBuffer(struct mad_pcm *pcm) {

    int length = pcm->length;
    const mad_fixed_t *left_ch = pcm->samples[0];
    const mad_fixed_t *right_ch = pcm->samples[1];


    for(int i=0; i< length; i++){
            int index = 4 * i;
            signed int left = scale(left_ch[i]);
            signed int right = scale(right_ch[i]);
            m_frame_buffer[index + 0 ] = ((left >> 0) & 0xff);
            m_frame_buffer[index +1] = ((left >> 8) & 0xff);
            m_frame_buffer[index+2 ] = ((right >> 0) & 0xff);
            m_frame_buffer[index +3] = ((right >> 8) & 0xff);
        } // for

}

char* MP3Reader::getStrError(enum mad_error error)
{
    char* str = new char[80];
    switch(error)
    {
        case MAD_ERROR_NONE:
            str = "NONE";
            break;
        case MAD_ERROR_BUFPTR:
            str = "BUFPTR";
            break;
        case MAD_ERROR_BUFLEN:
            str = "BUFLEN";
            break;
        case MAD_ERROR_NOMEM:
            str = "NOMEM";
            break;
        case MAD_ERROR_LOSTSYNC:
            str = "LOSTSYNC";
            break;
        case MAD_ERROR_BADLAYER:
            str = "BAD LAYER";
            break;
        case MAD_ERROR_BADBITRATE:
            str = "BAD BITRATE";
            break;
        case MAD_ERROR_BADSAMPLERATE:
            str = "BAD SAMPLERATE";
            break;
        case MAD_ERROR_BADEMPHASIS:
            str = "BAD EMPHASIS";
            break;
        case MAD_ERROR_BADCRC:
            str = "BAD CRC";
            break;
        case MAD_ERROR_BADBITALLOC:
            str = "BAD BITALLOC";
            break;
        case MAD_ERROR_BADSCALEFACTOR:
            str = "BAD SCALEFACTOR";
            break;
        case MAD_ERROR_BADMODE:
            str = "BAD MODE";
            break;
        case MAD_ERROR_BADFRAMELEN:
            str = "BAD FRAMELEN";
            break;
        case MAD_ERROR_BADBIGVALUES:
            str = "BAD BIGVALUES";
            break;
        case MAD_ERROR_BADBLOCKTYPE:
            str = "BAD BLOCKTYPE";
            break;
        case MAD_ERROR_BADSCFSI:
            str = "BAD SCFSI";
         break;
        case MAD_ERROR_BADDATAPTR:
            str = "BAD DATAPTR";
            break;
        case MAD_ERROR_BADPART3LEN:
            str = "BAD PART3LEN";
            break;
        case MAD_ERROR_BADHUFFTABLE:
            str = "BAD HUFFTABLE";
         break;
    case MAD_ERROR_BADHUFFDATA:
            str = "BAD HUFFDATA";
            break;
    case MAD_ERROR_BADSTEREO:
            str = "BAD STEREO";
            break;
    }
    return str;
}



/**
 * printFileInfo
 */
void MP3Reader::printFileInfo(void)
{
    int time = (float)m_total_frames / FRAMES_PER_SEC ;
    printf("File: %d bytes, %d frames \n",  m_file_size, m_total_frames);
    printf("playback: %d sec \n",  time);
}




/**
 * printPregress
 */
void MP3Reader::printPregress(void)
{

    int remain_frames = m_total_frames -  m_frame_count;
    if(remain_frames < 0){
            remain_frames = 0;
    }

    float remain_sec = (float)remain_frames / FRAMES_PER_SEC;
    fprintf(stderr, "\r [ %3d / %3d ] ( %3d sec)", 
            m_frame_count, m_total_frames, (int)remain_sec);
}


/**
 * printDecodedInfo
 */
void MP3Reader::printDecodedInfo(void)
{
	char	timer_dest[80];
    const char  *TIMER_FORMAT = "%lu: %02lu.%03u";
	mad_timer_string(m_mad_timer, 
                timer_dest, 
                TIMER_FORMAT,
				MAD_UNITS_MINUTES, MAD_UNITS_MILLISECONDS, 
                0 );
    fprintf(stderr, "\n");
	printf("decoded : %d frames ( %s ) \n",
				m_frame_count, timer_dest);
}


/**
 * printFrameInfo
 */
void MP3Reader::printFrameInfo(void)
{
        printf("frame length: %d \n", m_frame_length);
        printf("frame channels: %d \n", m_frame_channels);
        printf("frame samplerate: %d \n", m_frame_samplerate);
}

