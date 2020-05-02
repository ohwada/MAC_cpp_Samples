/**
 * OpenAL Beep
 * 2020-03-01 K.OHWADA
 */

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include<iostream>
#include <math.h>
#include <stdio.h>
#include<limits.h>
#include<unistd.h>

#ifndef __BEEP_H__
#define __BEEP_H__

#define BEEP_SAMPLINGRATE 44100

class Beep
{
public:
    int openAL(void);
    void closeAL(void);
    void playBeep(int frequency, int duration);
    int16_t* createTone(int frequency, int duration, int *size);

private:
    ALCdevice *m_device;
    ALCcontext *m_context;
    ALuint m_source;
    ALuint m_buffer;
};

#endif /* BEEP_H */

