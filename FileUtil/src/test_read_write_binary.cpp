/**
 *  test_read_write binary.cpp 
 * 2020-03-01 K.OHWADA
 */

// read write binary file 
// test for file_util.hpp

// g++ test_read_write_binary.cpp -o binary

#include <iostream>
#include <vector>
#include "file_util.hpp"


using namespace std;

 
/**
 * main
 */
int main(int argc, char** argv)
{ 

    string input( "../data/baboon.png" );
    string output( "baboon_out.png" );

    if(argc == 3) {
        input = argv[1];
        output = argv[2];
   } else {
        cout << "Usage:  " << argv[0] <<   " <Input filename> <Output filename>"  << endl;
    }

    vector<char> data;
    bool ret1 = readBinaryFile( input, data );
    if (!ret1){ 
        cerr << "open input file failed: " << input << endl;
        return EXIT_FAILURE;
    }  

    cout << "size: " << data.size() << endl;

    dumpBinary(data, 100);


    bool ret2 = writeBinaryFile( output, data );
    if (!ret2){ 
        cerr << "open output file failed: " << output << endl;
        return EXIT_FAILURE;
    } 

    cout << "write to: " << output << endl;

	return EXIT_SUCCESS;
}


