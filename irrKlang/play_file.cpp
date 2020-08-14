/**
 * irrKlang Sample
 * 2020-03-01 K.OHWADA
 */

// play file

#include <irrKlang.h>

#include <string>
#include <iostream>

#include "examples/conio.h"

using namespace std;
using namespace irrklang;


/**
 * main
 */
int main(int argc, const char** argv)
{

    const int ESC = 27;

    if (argc != 2) {
        cout << "Usage: " << argv[0]  << " <audioFile> " << endl;
        return EXIT_FAILURE;
    }

    char *input = (char *)argv[1];

	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
        cout << "Could not startup engine" << endl;
        return EXIT_FAILURE;
	}

	engine->play2D(input, true);

    cout << "play a sound looped" << endl;
    cout << endl;
	cout << "press ESC to quit" << endl;

    while(1)
	{
		if(getch() == ESC){
            break;
        }
	}

	engine->drop(); // delete engine

    return EXIT_SUCCESS;
}
