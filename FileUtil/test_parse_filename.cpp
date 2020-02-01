/**
 * C++ Sample
 * 2020-01-01 K.OHWADA
 */

#include <string> 
#include <iostream>
#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <filename> "  << endl;
        return 1;
    }

    // specify filename from commandline 
    string filename = argv[1];

    string dir;
    string title;
    string ext;
    parseFileName(filename, dir, title, ext);

    cout << filename  << endl;
    cout << dir <<  " , " << title   << " , " << ext  << endl;

    return 0;
}
