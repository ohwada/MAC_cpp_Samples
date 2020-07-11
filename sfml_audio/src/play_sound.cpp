/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// play sound file
// reference : https://www.sfml-dev.org/tutorials/2.5/audio-sounds.php

#include <string> 
#include<iostream>
#include<unistd.h>

#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

using namespace std;


/**
 * main
 */
int main(int argc, char** argv) 
{

    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <soundFile> "  << endl;
        return EXIT_FAILURE;
    }

    char *input =  argv[1];

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(input)){
        cout << "loadFromFile faild: " <<  input << endl;
        return EXIT_FAILURE;
    }

    sf::Time duration = buffer.getDuration();
    float playtime = duration.asSeconds();
    cout << "playtime: "<< playtime <<  " sec" << endl;

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // margin 2 sec
    sleep(playtime + 2);

    sound.stop ();

	return EXIT_SUCCESS;
}

