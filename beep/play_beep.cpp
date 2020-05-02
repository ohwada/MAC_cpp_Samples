/**
 * OpenAL Beep Sample
 * 2020-03-01 K.OHWADA
 */

// play beep sound with Beep class

#include "Beep.hpp"

using namespace std;

/**
 * main
 */
int main(int argc, char** argv)
{

	Beep beep;

    int freq = 440; // Hz
    int duration = 1000; // 1 sec

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " [freq] [duration] "  << endl;

    } else if(argc == 3) {
        freq = atoi(argv[1]);
        duration = atoi(argv[2]);

    } else if(argc == 2) {
        freq = atoi(argv[1]);
    }


// open
	int ret = beep.openAL();
	if (ret != 0){
		cout << "openAL Faild" << endl;
		return 1;
	}


	beep.playBeep(freq, duration);

// Cleanup
    beep.closeAL();

	return 0;
}

