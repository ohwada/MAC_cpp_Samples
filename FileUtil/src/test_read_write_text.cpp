/**
 * test_readwrite text_file.cpp 
 * 2020-03-01 K.OHWADA
 */

// test for file_util.hpp

#include <iostream>
#include "file_util.hpp"

using namespace std;

 
/**
 * main
 */
int main(int argc, char** argv)
{ 

    string input( "../data/sample.txt" );
    string output( "sample_out.txt" );

    if(argc == 3) {
        input = argv[1];
        output = argv[2];
    } else {
        cout << "Usage:  " << argv[0] <<   " <Input filename> <Output filename>"  << endl;
    }

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

	return EXIT_SUCCESS;
}


// ----------
// Mac
// ...
// ----------
// write to: output.txt

