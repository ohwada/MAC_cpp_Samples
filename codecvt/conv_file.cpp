/**
 * codecvt Sample
 * 2020-03-01 K.OHWADA
 */


// convert text file codeset to UTF-8
// https://cpprefjp.github.io/reference/codecvt/

// Note:
// codecvt is deprecated from c ++ 17

#include <codecvt>

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "TextReader.hpp"

#include "parse_filename.hpp"

using namespace std;

// global
TextReader reader;

/**
 * convLineToU8
 */
string convLineToU8(char* buf, int len, int debug)
{

    u16string u16 = reader.convLineToU16(buf, len, debug);

    string u8 = wstring_convert<
                codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);

    return u8;
}



/**
 * main
 */
int main( int argc, char **argv )
{

    const int BUF_SIZE  = 1024;
    char* buf = new char[BUF_SIZE];

    string input;
    int flag_debug = 0;

    ofstream ofs;

    if (argc == 3) {
        input = argv[1];
        flag_debug = atoi(argv[2]);
    } else if (argc == 2) {
        input = argv[1];
    } else{
        cout << "Usage: " << argv[0] << " <textFile> [debug] "  << endl;
        return EXIT_FAILURE;
    }

// output file
    string fname = getFileNameWithoutExt(input);
    string output = fname + "_utf8.txt";

    int enc_code = reader.getEnc(fname);
    if(enc_code == TEXT_READER_NONE){
            cout << "NOT find input encode code" << endl;
            return EXIT_FAILURE;
    }

    try {

        int ret1 = reader.open(input);
        if(ret1 != 0){
            cerr << "[FAILED] Could not open " << input << endl;
            return EXIT_FAILURE;
        }

        ofs.open(output);
        if (ofs.fail()) {
            cerr << "[FAILED] Could not open: " << output << endl;
            return EXIT_FAILURE;
        }


        bool flag_loop = true;
        while(flag_loop){

            int len = reader.getLine(buf, BUF_SIZE);
            if(len == TEXT_READER_EOF){
                flag_loop = false;
                break;
            }

                string u8 = convLineToU8(buf, len, flag_debug);

                cout << " : " << u8 << endl;
                ofs << u8 << endl;

        } // while

        reader.close();
        ofs.close();

    } catch (char *e) {
            cerr << "EXCEPTION : " << e << endl;
            return EXIT_FAILURE;
    }

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;

}

