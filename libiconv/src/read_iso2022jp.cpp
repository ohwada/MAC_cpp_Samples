/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// read ISO-2022JP file
// convert codeset to UTF-8
// write UTF-8 file


// g++ read_iso2022jp.cpp -std=c++11 `pkg-config --cflags --libs iconv` 


#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "iso2022jp.hpp"
#include "parse_filename.hpp"


using namespace std;


/*
 * main
 */
int main(int argc, char** argv)
{

    string input = "../samples/sample_iso2022jp.txt";

    if (argc == 2) {
        input = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <textFile> "  << endl;
    }

    cout << "input: " << input << endl;

    string fname = getFileNameWithoutExt( input );

    string output = fname + string("_utf8.txt");

    cout << "output: " << output << endl;



    ifstream ifs;
    ofstream ofs;


        // open input file
        ifs.open( input, std::ios::in); 
        if (ifs.fail()){ 
            cerr << "Could not open " << input << endl;
            return EXIT_FAILURE;
        }  

	    ofs.open( output , std::ios::binary | std::ios::out );
        if (ofs.fail()) {
            cerr << "Could not open " << output << endl;
            return EXIT_FAILURE;
        }


        string line;
        string text1;
        string text2;
        string error;
        int line_count = 0;
        bool is_error = false;


    while( getline(ifs, line) ) {

            line_count++;

// replace Line feed code(0x0A) to string terminator code(0x00)
// Escape sequence(0x1B, 0x28, 0x42) remains at the end

// remove Escape sequence
// iconv will convert correctly
// even if the Escape sequence remains
             removeLastEsc(line, text1);

            dumpString( text1 );

            bool ret1 = convFromIso2022jp( text1,  text2,  error );

            if ( ret1 ) {
                    cout << text2 << endl;
                    ofs << text2 << endl;
            } else {
                    is_error = true;
                    cerr <<  line_count << " : " << error << endl;
            }


            cout << endl;

    } // while

        ifs.close();
        ofs.close();

    if(is_error) {
            cerr << "failed" << endl;
            return EXIT_FAILURE;
    }

        cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

