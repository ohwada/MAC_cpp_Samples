/**
 * OpenAL Beep
 * 2020-03-01 K.OHWADA
 */


// reference : https://w.atwiki.jp/yosilove/pages/16.html


#include "Beep.hpp"

using namespace std;

// global
const int BEEP_MSEC_TO_USEC = 1000;
const float BEEP_MSEC_TO_SEC = 0.001;

/**
 *  open
 */
int Beep::openAL(void)
{
    m_device = alcOpenDevice(NULL);
	if (!m_device){
        printf("alcOpenDevice Faild \n");
		return 1;
	}

    m_context = alcCreateContext(m_device, NULL);
	if (!m_context){
        printf("alcOpenDevice Faild \n");
		return 2;
	}

   alcMakeContextCurrent(m_context);

   alGenSources(1, &m_source);
   alGenBuffers(1, &m_buffer);

    return 0;
}


/**
 *  closeAL
 */
void Beep::closeAL(void)
{
   alDeleteSources(1, &m_source);
   alDeleteBuffers(1, &m_buffer);
   alcMakeContextCurrent(NULL);
   alcDestroyContext(m_context);
   alcCloseDevice(m_device);
}


/**
 * playBeep
  * @param frequency : Hz
  * @param duration : msec
 */
void Beep::playBeep(int frequency, int duration)
{
    int tone_size;
    int16_t* data = createTone(frequency, duration, &tone_size);

    int usec = BEEP_MSEC_TO_USEC * duration;

    int m_buffer_size = tone_size * sizeof(int16_t);
	alBufferData(m_buffer, AL_FORMAT_MONO16, &data[0], m_buffer_size, BEEP_SAMPLINGRATE);

	alSourcei(m_source, AL_BUFFER, m_buffer);

	alSourcePlay(m_source);

	usleep(usec);

	alSourcePause(m_source);

}


/**
 * createTone
  * @param frequency : Hz
  * @param duration : msec
 * @return 16 bit 44.1 KHz sampling
 */
int16_t* Beep::createTone(int frequency, int duration, int *tone_size)
{

    int bufsize = BEEP_SAMPLINGRATE * BEEP_MSEC_TO_SEC * duration;
	int16_t* buff = new int16_t[bufsize];

// radian per sample rate
	double delta = (2 * M_PI * frequency ) / BEEP_SAMPLINGRATE;

// Generate Sin wave
	for (int i = 0; i < bufsize; i++) {
		buff[i] = SHRT_MAX * sin(delta * i);
	}

    *tone_size = bufsize;
	return buff;
}

