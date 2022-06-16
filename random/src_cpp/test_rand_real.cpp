/**
 * C++ sample
 * 2022-06-01 K.OHWADA
 */

// g++  gen_random_floatingcpp

// generate random floating point number vusing mt19937
// reference : https://qiita.com/_EnumHack/items/25fc998873d1bc7d2276
// https://marycore.jp/prog/cpp/stream-format-float/

#include<iostream>
#include <iomanip>
#include "rand.hpp"

using namespace std;

/**
 * main
 */
int main(int argc, char *argv[])
{

    const int  NUM = 10;

    double  min = 0.0;
    double  max = 1.0;

    if(argc == 3){
            min = atof(argv[1]);
            max = atof(argv[2]);
    } else {
            cout <<  "Usage: " << argv[0] << " [min] [max]" << endl;
    }

    cout << fixed << setprecision(1) << "random: " << min << " -> " << max << endl;

    for(int i=0; i<NUM; i++)
    {
        double r = genRandReal(min, max);
        cout  << fixed << setprecision(3)  << r << endl;
    }

    return EXIT_SUCCESS;
}

