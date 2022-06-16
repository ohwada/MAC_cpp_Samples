/**
 * random sample
 * 2022-06-01 K.OHWADA
 */

// test for random_string.hpp
// generate random string

#include<iostream>

#include "random_string.hpp"
 
using namespace std;


/**
 *  genRandomString
 */
string genRandomString(int mode, int length)
{
    string str;
    switch(mode)
    {   
        case  1:
            str = genRandomStringMix(length);
            break;
        case 2:
            str = genRandomStringLower(length);
            break;
        case 3: 
           str = genRandomStringUpper(length);
            break;
       case 4: 
           str = genRandomStringDigit(length);
            break;
        }

    return str;
}


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

    switch(mode)
    {
        case 1:
            cout << "mode 1: mix lowercase upercase degit" << endl;
            break;
        case 2:
            cout << "mode 2: lowercase" << endl;
            break;
        case 3:
            cout << "mode 3: uppercase" << endl;
            break;
       case 4:
            cout << "mode 4: degit" << endl;
            break;
        default:
            cout << "mode must be from 1 to 4" << endl;
            return EXIT_FAILURE;
    }


    for(int i=0; i<NUM; i++)
    {
            string str = genRandomString(mode, LENGTH);
            cout << str << endl;
    }


    return EXIT_SUCCESS;
}

