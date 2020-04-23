/**
 * OpenAL Sample
 * 2020-03-01 K.OHWADA
 * oroginal : https://gist.github.com/skitaoka/d44d08be9ca1ed690918
 */


#include <string> 
#include <iostream>

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <OpenAL/alure.h>

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "alure Version: " << ALURE_VERSION_STRING << endl;

  if (argc != 2) {
    cout << "usage: " << argv[0] << "<wavfile> " << endl;
    return 1;
  }

   char* input = argv[1];

// InitDevice
  if (!alureInitDevice(NULL, NULL)) {
    cout<< "failed to initialize alure!" << endl;
    return 1;
  }

  ALuint source;
  alGenSources(1, &source);

// read file
  ALuint buffer = alureCreateBufferFromFile(input);
  if (buffer == AL_NONE) {
    cout << " alureCreateBufferFromFile Faild: " << input << endl;
    return 1;
  }

    cout << " alureCreateBufferFromFile: " << input << endl;

// play
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    cout << "alSourcePlay"<< endl;

// wait to finish
    ALint state = AL_PLAYING;
    while (1)
    {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING){
            // finish
            break;
        }

        ALenum err = alGetError(); 
        if(err != AL_NO_ERROR){
            cout << "play Faild: " << err << endl;
            break;
        }

        alureSleep(0.1f);
  }


// cleanup
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  alureShutdownDevice();

  return 0;
}
