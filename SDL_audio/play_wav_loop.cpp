/**
 * SDL Audio Sample
 * 2020-03-01 K.OHWADA
 */


// play wav file  in endless loop
// original : https://www.libsdl.org/tmp/SDL/test/loopwave.c


/*
  Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/

/* Program to load a wave file and loop playing it using SDL audio */

/* loopwaves.c is much more robust in handling WAVE files --
    This is only for simple WAVEs
*/

#include <SDL.h>

#include <string> 
#include<iostream>

using namespace std;


/**
 * struct wave
 */
static struct
{
    SDL_AudioSpec spec;
    Uint8 *sound;               /* Pointer to wave data */
    Uint32 soundlen;            /* Length of wave data */
    int soundpos;               /* Current play position */
} wave;


// global
static SDL_AudioDeviceID device;



/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void quit(int rc)
{
    SDL_Quit();
    exit(rc);
}


/**
 * close_audio
 */
static void close_audio()
{
    if (device != 0) {
        SDL_CloseAudioDevice(device);
        device = 0;
    }
}


/**
 * open_audio
 */
static void open_audio()
{
    /* Initialize fillerup() variables */
    device = SDL_OpenAudioDevice(NULL, SDL_FALSE, &wave.spec, NULL, 0);
    if (!device) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open audio: %s\n", SDL_GetError());
        SDL_FreeWAV(wave.sound);
        quit(2);
    }


    /* Let the audio run */
    SDL_PauseAudioDevice(device, SDL_FALSE);
}


/**
 * reopen_audio
 */
static void reopen_audio()
{
    close_audio();
    open_audio();
}


/**
 * fillerup
 */
void SDLCALL fillerup(void *unused, Uint8 * stream, int len)
{
    Uint8 *waveptr;
    int waveleft;

    /* Set up the pointers */
    waveptr = wave.sound + wave.soundpos;
    waveleft = wave.soundlen - wave.soundpos;

    /* Go! */
    while (waveleft <= len) {
        SDL_memcpy(stream, waveptr, waveleft);
        stream += waveleft;
        len -= waveleft;
        waveptr = wave.sound;
        waveleft = wave.soundlen;
        wave.soundpos = 0;
    }
    SDL_memcpy(stream, waveptr, len);
    wave.soundpos += len;
}




/**
 * main
 */
int main(int argc, char **argv)
{

    int done = 0;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Load the SDL library */
    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <wavFile> " <<  endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];


    /* Load the wave file into memory */
    if (SDL_LoadWAV(input, &wave.spec, &wave.sound, &wave.soundlen) == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load %s: %s\n", input, SDL_GetError());
        return EXIT_FAILURE;
    }

    int soundlen  = wave.soundlen;
    int freq = wave.spec.freq;
    int channels = wave.spec.channels;
    int format = wave.spec.format;

    cout << "soundlen: " << soundlen <<  endl;
    cout << "freq: " << freq <<  endl;
    cout << "channels: " << channels <<  endl;
    cout << "format: " << format <<  endl; 

    wave.spec.callback = fillerup;

    /* Show the list of available drivers */
    SDL_Log("Available audio drivers:");
    for (int i = 0; i < SDL_GetNumAudioDrivers(); ++i) {
        SDL_Log("%i: %s", i, SDL_GetAudioDriver(i));
    }

    SDL_Log("Using audio driver: %s\n", SDL_GetCurrentAudioDriver());

    open_audio();

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event) > 0) {

            if (event.type == SDL_QUIT) {
                done = 1;
            }

            if ((event.type == SDL_AUDIODEVICEADDED && !event.adevice.iscapture) ||
                (event.type == SDL_AUDIODEVICEREMOVED && !event.adevice.iscapture && event.adevice.which == device)) {
                reopen_audio();
                cout << "reopen_audio" <<  endl;
            }

        } // while : SDL_PollEven

        SDL_Delay(100); // 100 msec

    } // while : done


    /* Clean up on signal */
    close_audio();
    SDL_FreeWAV(wave.sound);
    SDL_Quit();

    return EXIT_SUCCESS;
}

