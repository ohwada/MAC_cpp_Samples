/**
 * utf_converter Sample
 * 2020-03-01 K.OHWADA
 */


// convert text file codeset to UTF-8 with utf_converter


#include <string>
#include <iostream>
#include <fstream>

#include "utf_converter.hpp"

#include "../line.h"

#include "../parse_filename.hpp"

using namespace std;


/**
 * convLineToU8
 */
string convLineToU8(string str, int enc, int debug)
{

    std::string u8;

    if(enc == 16){
        u16string u16 = convLineToU16(str, debug);
        ConvU16ToU8(u16, u8);
    }else if(enc == 32){
        u32string u32 = convLineToU32(str, debug);
        ConvU32ToU8(u32, u8);
    }

    return u8;
}


/**
 * getInputEncode
 */
int getInputEncode(string filename)
{
    int enc = 0;
    string parse_encode = "";
    int pos  = filename.find_last_of('_');
    if (pos != std::string::npos) {
        parse_encode = filename.substr(pos+1, filename.size()-pos);
    }

    if(parse_encode == "utf16be"){
        enc = 16;
    }else if(parse_encode == "utf32be"){
        enc = 32;
    }

    return enc;
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

    int enc = getInputEncode(fname);

    try {

        ifs.open(input);
        if (ifs.fail()) {
            cerr << "[FAILED] Could not open " << input << endl;
            return EXIT_FAILURE;
        }

        ofs.open(output);
        if (ofs.fail()) {
            cerr << "[FAILED] Could not open " << output << endl;
            return EXIT_FAILURE;
        }

         string line;

        while (getline(ifs, line)) {

                string u8 = convLineToU8(line, enc, flag_debug);

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

