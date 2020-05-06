/**
 * SDL Audio Sample
 * 2020-02-01 K.OHWADA
 */


// play beep
// reference : https://stackoverflow.com/questions/10110905/simple-sound-wave-generator-with-sdl-in-c

#include <SDL.h>
#include <SDL_audio.h>

#include <string>
#include<iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include<limits.h>

using namespace std;

// global
const int BEEP_SAMPLINGRATE = 44100;
const int BEEP_CHANNELS_MONO = 1;
int g_freq;


/**
 * audio_callback
 */
void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
{
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 2; // 2 bytes per sample for AUDIO_S16SYS

    // TODO
    //int &sample_nr(*(int*)user_data);
    int sample_nr = 0;

    for(int i = 0; i < length; i++)
    {
        sample_nr++;
        double time = (double)i / (double)BEEP_SAMPLINGRATE;
        buffer[i] = (Sint16)(SHRT_MAX * sin(2.0f * M_PI * (float)g_freq * time));
    }

}


/**
 * main
 */
int main(int argc, char **argv)
{

    const int BEEP_SAMPLES = 2048;

    int duration = 1; // 1 sec
    int delay;
    g_freq = 440; // Hz

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " [freq] [duration] "  << endl;

    } else if(argc == 3) {
        g_freq = atoi(argv[1]);
        duration = atoi(argv[2]);

    } else if(argc == 2) {
        g_freq = atoi(argv[1]);
    }

    delay = 1000 * duration; // msec to sec

    SDL_AudioSpec have;
    int sample_nr = 0;

    if(SDL_Init(SDL_INIT_AUDIO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    }

    SDL_AudioSpec want;
    want.freq = BEEP_SAMPLINGRATE; // number of samples per second
    want.format = AUDIO_S16SYS; // sample type (here: signed short i.e. 16 bit)
    want.channels = BEEP_CHANNELS_MONO; // only one channel
    want.samples = BEEP_SAMPLES; // buffer-size
    want.callback = audio_callback; // function SDL calls periodically to refill the buffer
    want.userdata = &sample_nr; // counter, keeping track of current sample number


    if(SDL_OpenAudio(&want, &have) != 0){ 
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
    }

    if(want.format != have.format) {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");
    }

    SDL_PauseAudio(0); // start playing sound
    SDL_Delay(delay); // wait while sound is playing
    SDL_PauseAudio(1); // stop playing sound

    SDL_CloseAudio();

    return 0;
}

