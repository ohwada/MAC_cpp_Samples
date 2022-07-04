/**
 * ogg_eader.cpp
 * 2020-03-01 K.OHWADA
 */



 #include "ogg_reader.hpp"

using namespace std;


// constant
const int READ_ENDIAN_LITTLE = 0;  //  little endian
const int READ_WORD_16 = 2;  // 16-bit samples
const int READ_SIGN_SIGNED = 1;  // signed

const int MARGIN_FRAMES_JUDGE_END = 10;


/**
 * constractor
 */
OggReader::OggReader(void)
{
    m_ov_buffer = new char[OGG_READER_BUFF_SIZE];

    FRAMES_PER_SEC = (float)OGG_READER_SAMPLINGRATE / (float )OGG_READER_BUFF_SIZE ;

}


/**
 * destractor
 */
OggReader::~OggReader(void)
{
    delete [] m_ov_buffer;
}


/**
 * open
 */
int OggReader::open(char *filename)
{
    // open input
    m_fp = fopen(filename, "rb");
	if (!m_fp){
		return OGG_ERR_FOPEN;
	}

    // open ogg Vorbis
    int ret = ov_open(m_fp, &m_ovf, NULL, 0);
	if (ret != 0){
        fclose(m_fp);
		return OGG_ERR_OVOPEN;
	}

	m_total = ov_pcm_total(&m_ovf, -1);

    m_frame_count = 0;

    m_total_frames = ( m_total / OGG_READER_BUFF_SIZE ) ;

    return OGG_OPEN_SUCCESS;
}


/**
 * close
 */
void OggReader::close(void)
{
    fclose(m_fp);
    ov_clear(&m_ovf);
}


/**
 * read
 */
int OggReader::read(void)
{
// if the passed in buffer is large, ov_read() will not fill it
// the passed in buffer size is treated as a limit and not a request. 
        int ov_current = 0;
       m_read_size = ov_read(
            &m_ovf, 
            m_ov_buffer, 
            OGG_READER_BUFF_SIZE, 
            READ_ENDIAN_LITTLE,
            READ_WORD_16, 
            READ_SIGN_SIGNED,
            &ov_current );

        if (m_read_size == 0) {
            //  read all the ov_data
                return OGG_READER_END;
        }

        m_frame_count ++;
        if(m_frame_count > (m_total_frames + MARGIN_FRAMES_JUDGE_END)){
                return OGG_READER_END;
        }

// ov_info
        vorbis_info *info = ov_info(&m_ovf, -1);
        m_ov_version = info->version;
        m_ov_channels = info->channels;
        m_ov_rate = info->rate;

          return OGG_READER_CONTINUE;
}


/**
 * getBuffer
 */
char* OggReader::getBuffer(void)
{
    return m_ov_buffer;
}


/**
 * printFileInfo
 */
void OggReader::printFileInfo(void)
{
    int time = (float)m_total_frames / FRAMES_PER_SEC ;
    printf("File: %d bytes %d frames \n", m_total, m_total_frames);
    printf("playback: %d sec \n",  time);
}


/**
 * printOvInfo
 */
void OggReader::printOvInfo(void)
{
        printf("vorbis_info version = %d \n", m_ov_version);
        printf("vorbis_info channels = %d \n", m_ov_channels);
        printf("vorbis_info rate = %ld \n", m_ov_rate);
}


/**
 * printPregress
 */
void OggReader::printPregress(void)
{

    int remain_frames = m_total_frames -  m_frame_count;
    if(remain_frames < 0){
            remain_frames = 0;
    }

    float remain_sec = (float)remain_frames / FRAMES_PER_SEC;
    fprintf(stderr, "\r [ %3d / %3d ] ( %3d sec)", 
            m_frame_count, m_total_frames, (int)remain_sec);
}

