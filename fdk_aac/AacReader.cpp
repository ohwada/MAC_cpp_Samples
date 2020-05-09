/**
 * fdk aac Sample
 * 2020-03-01 K.OHWADA
 */

// aac decoder
// original : https://github.com/akanchi/aac-example


#include "AacReader.hpp"


const int FRAME_SIZE = 1024;
const int PCM_SIZE = 4 * FRAME_SIZE;
const int PCM_BUF_SIZE = 8 * FRAME_SIZE;

// rough  sloppy value for progress
const float COMPRESSION_RATIO = 10.0;


/**
 * constractor
 */
AacReader::AacReader()
{

	m_pcm_buffer = new char [PCM_BUF_SIZE];

	m_aacdec.dec = NULL;
	m_frame_count = 0;
	m_sum_pcm_size = 0;
    m_is_first = true;

    // calculate roughly
    FRAMES_PER_SEC = (float)AAC_READER_SAMPLINGRATE / (float )FRAME_SIZE ;

}


/**
 * destractor
 */
AacReader::~AacReader()
{

	 delete[] m_pcm_buffer;
	aacdec_close();

}


/**
 * readFile
 */
int  AacReader::readFile(char *filename)
{

	int ret = open(filename);
    if(ret != 0){
        return ret;
    }

	printFileInfo();
    close();
    return 0;

}


/**
 * open
 */
int  AacReader::open(char *filename)
{

    // open  file
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


	aacdec_init_adts();

    // create buffer
    m_aac_buffer = new char [m_file_size];


    // read all data
    int rsize = fread(m_aac_buffer, 1, m_file_size, m_fp);
    if(rsize != m_file_size){
        fclose(m_fp);
        return 3;
    }

    m_aac_size = m_file_size;
    m_pos = 0;

    // calculate roughly
    m_total_frames = COMPRESSION_RATIO * ( m_file_size / PCM_SIZE ) ;

    return 0;
}


/**
 * close
 */
void AacReader::close(void)
{
        fclose(m_fp);
}


/**
 * freeBuffer
 */
void AacReader::freeBuffer(void)
{
	delete[]m_aac_buffer;
}


/**
 * decodeAac
 */
int AacReader::decodeAac(void)
{
	m_frame_count++;

    if (m_aac_size - m_pos < 7) {
			return AAC_READER_END;
    }

	// pointer 
	char* ptr_aac_buf = (char*)&m_aac_buffer[m_pos];
	adts_header_t *adts = (adts_header_t *)ptr_aac_buf;

    if (adts->syncword_0_to_8 != 0xff || adts->syncword_9_to_12 != 0xf) {
				return AAC_READER_END;
	}

	int aac_frame_size = adts->frame_length_0_to_1 << 11 | adts->frame_length_2_to_9 << 3 | adts->frame_length_10_to_12;

	if (m_pos + aac_frame_size > m_aac_size) {
				return AAC_READER_END;
	}

    int leftSize = aac_frame_size;
    int ret = aacdec_fill( ptr_aac_buf, aac_frame_size, &leftSize);

    m_pos += aac_frame_size;
    //printf("m_pos: %d \n", m_pos);

    if (ret != 0) {
				return AAC_READER_CONTINUE;
	}

	if (leftSize > 0) {
				return AAC_READER_CONTINUE;
	}

	m_pcm_buffer_valid_size = 0;

	ret = aacdec_decode_frame(m_pcm_buffer,  PCM_BUF_SIZE,  &m_pcm_buffer_valid_size);

    if (ret == AAC_DEC_NOT_ENOUGH_BITS) {
				return AAC_READER_CONTINUE;
	}

	if (ret != 0) {
				return AAC_READER_CONTINUE;
	}


    int sample_rate = aacdec_sample_rate();
	if (sample_rate <= 0) {
				return AAC_READER_END;
	}


	if(sample_rate != AAC_READER_SAMPLINGRATE){
        printf("sample_rate: %d \n", sample_rate);
        return AAC_READER_CONTINUE;
    }

	if(m_pcm_buffer_valid_size != PCM_SIZE){
        printf("pcm_buffer_valid_size: %d \n", m_pcm_buffer_valid_size);
        return AAC_READER_CONTINUE;
    }


    if(m_is_first){
        m_is_first = false;
        printFrameInfo();
    }

    m_sum_pcm_size += m_pcm_buffer_valid_size;

    return AAC_READER__SUCCESS;
}


/**
 * aacdec_init_adts
 */
int AacReader::aacdec_init_adts()
{

	m_aacdec.sample_bits = 16;
	m_aacdec.is_adts = 1;
	m_aacdec.filled_bytes = 0;

	m_aacdec.dec = aacDecoder_Open(TT_MP4_ADTS, 1);
	if (!m_aacdec.dec) {
		return -1;
	}

	m_aacdec.info = NULL;

	return 0;
}


/**
 * aacdec_close
 */
void AacReader::aacdec_close()
{
	if (m_aacdec.dec) {
		aacDecoder_Close(m_aacdec.dec);
	}
	m_aacdec.dec = NULL;
}


/**
 * aacdec_fill
 */
int AacReader::aacdec_fill(char *data, int nb_data, int *pnb_left)
{

	m_aacdec.filled_bytes += nb_data;

	unsigned char *udata = (unsigned char *)data;
	unsigned int unb_data = (unsigned int)nb_data;
	unsigned int unb_left = unb_data;
	AAC_DECODER_ERROR err = aacDecoder_Fill(m_aacdec.dec, &udata, &unb_data, &unb_left);
	if (err != AAC_DEC_OK) {
		return err;
	}

	if (pnb_left) {
		*pnb_left = (int)unb_left;
	}

	return 0;
}


/**
 * aacdec_sample_bits
 */
int AacReader::aacdec_sample_bits()
{
	return m_aacdec.sample_bits;
}


/**
 * aacdec_pcm_size
 */
int AacReader::aacdec_pcm_size()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return (int)(m_aacdec.info->numChannels * m_aacdec.info->frameSize * m_aacdec.sample_bits / 8);
}


/**
 * aacdec_decode_frame
 */
int AacReader::aacdec_decode_frame(char *pcm, int nb_pcm, int *pnb_valid)
{
	// when buffer left bytes not enough, directly return not-enough-bits.
	// we requires atleast 7bytes header for adts.
	if (m_aacdec.is_adts && m_aacdec.info && m_aacdec.filled_bytes - m_aacdec.info->numTotalBytes <= 7) {
		return AAC_DEC_NOT_ENOUGH_BITS;
	}

	INT_PCM* upcm = (INT_PCM*)pcm;
	int unb_pcm = (int)nb_pcm;
	AAC_DECODER_ERROR err = aacDecoder_DecodeFrame(m_aacdec.dec, upcm, unb_pcm, 0);
	// user should fill more bytes then decode.
	if (err == AAC_DEC_NOT_ENOUGH_BITS) {
		return err;
	}
	if (err != AAC_DEC_OK) {
		return err;
	}

	// when decode ok, retrieve the info.
	if (!m_aacdec.info) {
		m_aacdec.info = aacDecoder_GetStreamInfo(m_aacdec.dec);
	}

	// the actual size of pcm.
	if (pnb_valid) {
		*pnb_valid = aacdec_pcm_size();
	}

	return 0;
}


/**
 *  aacdec_sample_rate
 */
int AacReader::aacdec_sample_rate()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->sampleRate;
}


/**
 *  aacdec_frame_size
 */
int AacReader::aacdec_frame_size()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->frameSize;
}


/**
 *  aacdec_num_channels
 */
int AacReader::aacdec_num_channels()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->numChannels;
}


/**
 *  aacdec_aac_sample_rate
 */
int AacReader::aacdec_aac_sample_rate()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->aacSampleRate;
}


/**
 *  aacdec_profile
 */
int AacReader::aacdec_profile()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->profile;
}


/**
 *  aacdec_audio_object_type
 */
int AacReader::aacdec_audio_object_type()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->aot;
}


/**
 *  aacdec_channel_config
 */
int AacReader::aacdec_channel_config()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->channelConfig;
}


/**
 *  aacdec_bitrate
 */
int AacReader::aacdec_bitrate()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->bitRate;
}


/**
 *  acdec_aac_samples_per_frame
 */
int AacReader::aacdec_aac_samples_per_frame()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->aacSamplesPerFrame;
}


/**
 *  aacdec_aac_num_channels
 */
int AacReader::aacdec_aac_num_channels()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->aacNumChannels;
}


/**
 *  aacdec_extension_audio_object_type
 */
int AacReader::aacdec_extension_audio_object_type()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->extAot;
}


/**
 *  aacdec_extension_sampling_rate
 */
int AacReader::aacdec_extension_sampling_rate()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->extSamplingRate;
}


/**
 *  aacdec_num_lost_access_units
 */
int AacReader::aacdec_num_lost_access_units()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->numLostAccessUnits;
}


/**
 *  aacdec_num_total_bytes
 */
int AacReader::aacdec_num_total_bytes()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->numTotalBytes;
}


/**
 *  aacdec_num_bad_bytes
 */
int AacReader::aacdec_num_bad_bytes()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->numBadBytes;
}


/**
 *  aacdec_num_total_access_units
 */
int AacReader::aacdec_num_total_access_units()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->numTotalAccessUnits;
}


/**
 *  aacdec_num_bad_access_units
 */
int AacReader::aacdec_num_bad_access_units()
{
	if (!m_aacdec.info) {
		return 0;
	}
	return m_aacdec.info->numBadAccessUnits;
}


/**
 * getPcmData
 */
char* AacReader::getPcmData(void)
{
    return m_pcm_buffer;
}


/**
 * getPcmDataSize
 */
int AacReader::getPcmDataSize(void)
{
    return m_pcm_buffer_valid_size;
}


/**
 * getFrameSize
 */
int AacReader::getFrameSize(void)
{
    return aacdec_frame_size();
}


/**
 *  getSampleRate
 */
int AacReader::getSampleRate(void)
{
        return aacdec_sample_rate();
}


/**
 *  getChannels
 */
int AacReader::getChannels(void)
{
    return aacdec_num_channels();
}



/**
 * printFileInfo
 */
void AacReader::printFileInfo(void)
{
    // calculate roughly
    int time = (float)m_total_frames / FRAMES_PER_SEC ;
    printf("File: %d bytes, %d frames \n",  m_file_size, m_total_frames);
    printf("playback: %d sec \n",  time);
}


/**
 * printPregress
 */
void AacReader::printPregress(void)
{

    int remain_frames = m_total_frames -  m_frame_count;
    if(remain_frames < 0){
            remain_frames = 0;
    }

    // calculate roughly
    float remain_sec = (float)remain_frames / FRAMES_PER_SEC;

    fprintf(stderr, "\r [ %3d / %3d ] ( %3d sec)", 
            m_frame_count, m_total_frames, (int)remain_sec);
}


/**
 *  printDecodeInfo
 */
void AacReader::printDecodeInfo(void){
    printf("decoded: %d frames, %d bytes \n", m_frame_count, m_sum_pcm_size);
}


/**
 *  printFrameInfo
 */
void AacReader::printFrameInfo(void)
{
        printf("sample_rate: %d \n", aacdec_sample_rate());
        printf("channels: %d \n", aacdec_num_channels());
        printf("bit rate: %d \n", aacdec_bitrate());
    printf("pcm_size: %d \n", aacdec_pcm_size() );
        printf("frame size: %d \n", aacdec_frame_size());
        printf("samples per frame: %d \n", aacdec_aac_samples_per_frame());
        //printf("num_total_bytes: %d \n", aacdec_num_total_bytes());

}


