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

#include "line.h"

#include "parse_filename.hpp"

using namespace std;


/**
 * convLineToU8
 */
string convLineToU8(string str, int debug)
{

    u16string u16 = convLineToU16(str, debug);

    string u8 = wstring_convert<
                codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);

    return u8;
}



/**
 * main
 */
int main( int argc, char **argv )
{

    string input;
    int flag_debug = 0;

    ifstream ifs;
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

    try {

        ifs.open(input);
        if (ifs.fail()) {
            cerr << "[FAILED] Could not open: " << input << endl;
            return EXIT_FAILURE;
        }

        ofs.open(output);
        if (ofs.fail()) {
            cerr << "[FAILED] Could not open: " << output << endl;
            return EXIT_FAILURE;
        }


         string line;

        while (getline(ifs, line)) {

                string u8 = convLineToU8(line, flag_debug);

                cout << " : " << u8 << endl;
                ofs << u8 << endl;

        } // while

        ifs.close();
        ofs.close();

    } catch (char *e) {
            cerr << "EXCEPTION : " << e << endl;
            return EXIT_FAILURE;
    }

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;

}

