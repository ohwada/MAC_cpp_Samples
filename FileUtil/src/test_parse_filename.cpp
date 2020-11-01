/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// parse file fullpath
// test for parse_filename.hpp

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

    string basename = getFileNameWithExt(filename);
    string fname = getFileNameWithoutExt(filename);
    string fext = getFileNameExt(filename);

    cout <<  "FileNameWithExt: " << basename << endl;
    cout <<  "FileNameWithoutExt: " << fname << endl;
    cout <<  "FileNameExt: " << fext << endl;

	return EXIT_SUCCESS;
}


// % ./a.out data/sample.txt
// data/sample.txt
// data/ , sample , txt
// FileNameWithExt: sample.txt
// FileNameWithoutExt: sample
// FileNameExt: txt

