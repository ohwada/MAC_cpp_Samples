/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// play music file
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
        cout << "Usage: " << argv[0] << " <musicFile> "  << endl;
        return EXIT_FAILURE;
    }

    char *input =  argv[1];

    sf::Music music;
    if (!music.openFromFile(input)){
        cout << "loadFromFile faild: " <<  input << endl;
        return EXIT_FAILURE;
    }


    sf::Time duration = music.getDuration();
    float playtime = duration.asSeconds();
    cout << "playtime: " << playtime <<  " sec" << endl;

    music.play();

    int time_count = 0;
    while(true){

        sleep(1);  // 1 sec

        time_count ++;
        // margin 2 sec
        if(time_count > playtime + 2){
            break;
        }

		// progess info
		int time_remain = playtime - time_count;
        if(time_remain < 0){
            time_remain = 0;
        }
    	fprintf(stderr, "\r ( %3d sec)",  time_remain);

    }// while

    fprintf(stderr, "\n");
    music.stop ();

	return EXIT_SUCCESS;
}

