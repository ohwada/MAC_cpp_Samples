/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// read UTF-8 file
// convert codeset UTF-8 to ISO-2022-JP
// write ISO-2022-JP file

// g++ write_iso2022jp.cpp -std=c++11 `pkg-config --cflags --libs iconv` 


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

    string input = "../samples/sample_utf8.txt";

    if (argc == 2) {
        input = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <textFile> "  << endl;
    }

    cout << "input: " << input << endl;

    string fname = getFileNameWithoutExt( input );

    string output = fname + string("_iso2022jp.txt");

    cout << "output: " << output << endl;


    ifstream ifs;
    ofstream ofs;

        // open input file
        ifs.open( input, std::ios::in); 
        if (ifs.fail()){ 
            cerr << "Could not open " << input << endl;
            return EXIT_FAILURE;
        }  

	    // ofs.open( output, std::ios::binary | std::ios::out );
	    ofs.open( output,  std::ios::out );

        if (ofs.fail()) {
            cerr << "Could not open " << output << endl;
            return EXIT_FAILURE;
        }

        string line;
        string text;
        string text2;
        string error;
        int line_count = 0;
        bool is_error = false;


    while( getline(ifs, line) ) {

            line_count++;
            cout << "line: " << line << endl;

            bool ret1 = convToIso2022jp( line,  text,  error );

            if ( ret1 ) {
                    dumpString( text );

                    //ofs.write( (char *)text.c_str(), text.length() );
                    //ofs.write( (char *)ISO2022JP_LF, strlen(ISO2022JP_LF) );

ofs << text;
ofs << ISO2022JP_LF;

            } else {
                    is_error = true;
                    cerr <<  line_count << " : " << error << endl;
            }

         bool ret2 = convFromIso2022jp( text,  text2,  error );

            if ( ret2 ) {
                    cout << "conv: " << text2 << endl;
           } else {
                    is_error = true;
                    cerr <<  line_count << " : " << error << endl;
            }

            if( line != text2 ){
                    is_error = true;
                   cerr <<  line_count << " : unmatch " << endl;
            }

            cout << endl;

        } // while

        ifs.close();

        ofs.flush();
        ofs.close();

    if(is_error) {
            cerr << "failed" << endl;
            return EXIT_FAILURE;
    }

        cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

