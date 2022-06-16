/**
 * C++ sample
 * 2022-06-01 K.OHWADA
 */

// generate random integer using mt19937
// reference : ://vivi.dyndns.org/tech/cpp/random.html

#include<iostream>
#include "rand.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{
    const int  NUM = 10;

    int  min = 0;
    int  max = 999;

    if(argc == 3){
            min = atoi(argv[1]);
            max = atoi(argv[2]);
    } else {
            cout <<  "Usage: " << argv[0] << " [min] [max]" << endl;
    }

    cout << "random: " << min << " -> " << max << endl;

    for(int i=0; i<NUM; i++)
    {
        int r = genRandInt(min, max);
        cout << r << endl;
    }

    return EXIT_SUCCESS;
}
