/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// play sin wave tone
// http://www.site-a.info/programming/sfml/tutorials/2.1/audio-sounds.html

#include <string> 
#include<iostream>
#include<math.h>
#include<unistd.h>

#include <SFML/Audio.hpp>

using namespace std;

// global
const int SAMPLINGRATE = 44100;
const int CHANNELS = 1;


/**
 * createTone
  * @param frequency : Hz
  * @param duration : sec
 * @return 16 bit 44.1 KHz sampling
 */
int16_t* createTone(int freq, int duration, int *tone_size)
{

    int bufsize = SAMPLINGRATE  * duration;
	int16_t* buff = new int16_t[bufsize];

// radian per sample rate
	double delta = (2 * M_PI * freq ) / SAMPLINGRATE;

// Generate Sin wave
	for (int i = 0; i < bufsize; i++) {
		buff[i] = SHRT_MAX * sin(delta * i);
	}

    *tone_size = bufsize;
	return buff;
}


/**
 * main
 */
int main(int argc, char** argv) 
{
    int freq = 440; // Hz
    int duration = 1; //sec

    if(argc == 3) {
        freq = atoi(argv[1]);
        duration = atoi(argv[2]);

    } else if(argc == 2) {
        freq = atoi(argv[1]);
    } else {
        cerr << "Usage: " << argv[0] << " [freq] [duration] "  << endl;
    }

    int sample_size;
    int16_t* samples =  createTone(freq, duration, &sample_size);

    sf::SoundBuffer buffer;

    buffer.loadFromSamples(samples, sample_size, CHANNELS, SAMPLINGRATE);

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // margin 2 sec
    sleep(duration + 2);

    sound.stop ();
    delete[] samples;

	return EXIT_SUCCESS;
}
