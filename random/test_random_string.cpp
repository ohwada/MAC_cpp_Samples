/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// test for random_string.hpp
// generate random string

#include<iostream>

#include "random_string.hpp"
 
using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{
    const int LENGTH = 10;
    const int NUM = 10;

    int mode = 1; // upper lower mix

    if(argc == 2){
            mode = atoi(argv[1]);
    } else {
            cout <<  "Usage: " << argv[0] << " [mode]" << endl;
    }

        if(mode == 1){
            cout << "mode 1: mix lowercase upercase degit" << endl;
        } else if (mode == 2){
            cout << "mode 2: lowercase" << endl;
        } else if (mode == 3){ 
            cout << "mode 3: uppercase" << endl;
       } else if (mode == 4){ 
            cout << "mode 4: degit" << endl;
        } else {
            cout << "mode must be from 1 to 4" << endl;
            return EXIT_FAILURE;
        }

    string str;
    for(int i=0; i<NUM; i++)
    {
        if(mode == 1){
            str = genRandomStringMix(LENGTH);
        } else if (mode == 2){
            str = genRandomStringLower(LENGTH);
        } else if (mode == 3){ 
           str = genRandomStringUpper(LENGTH);
       } else if (mode == 4){ 
           str = genRandomStringDegit(LENGTH);
        }
        cout << str << endl;
    }

    return EXIT_SUCCESS;
}

