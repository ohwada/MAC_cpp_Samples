/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// read write text file 
// test for text_file.hpp

#include <iostream>
#include "file_text.hpp"

using namespace std;

 
/**
 * main
 */
int main(int argc, char** argv)
{ 

    if(argc < 3) {
        cout << "Usage:  " << argv[0] <<   " <Input filename> <Output filename>"  << endl;
        return 1;
    }

    // specify filename from commandline 
    string input = argv[1];
    string output = argv[2];

    string text;
    bool ret1 = readTextFile( input, text );
    if (!ret1){ 
        cerr << "open input file failed: " << input << endl;
        return 1;
    }  

    cout<< "----------" << endl;
    cout<< text << endl;
    cout<< "----------" << endl;

    bool ret2 = writeTextFile( output, text );
    if (!ret2){ 
        cerr << "open output file failed: " << output << endl;
        return 1;
    } 

    cout << "write to: " << output << endl;

    return 0;
}


// ----------
// Mac
// ...
// ----------
// write to: output.txt


