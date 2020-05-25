/**
 * utf converter Sample
 * 2020-03-01 K.OHWADA
 */


// convert text file codeset to UTF-8 with utf_converter


#include <string>
#include <iostream>
#include <fstream>

#include "utf_converter.hpp"

#include "../TextReader.hpp"

#include "../parse_filename.hpp"

using namespace std;

// global
TextReader reader;

/**
 * convLineToU8
 */
string convLineToU8(char* buf, int len,  int enc, int debug)
{

    std::string u8;

    if(enc == TEXT_READER_UTF16BE){
        u16string u16 = reader.convLineToU16(buf, len, debug);
        ConvU16ToU8(u16, u8);
    }else if(enc == TEXT_READER_UTF32BE){
        u32string u32 = reader.convLineToU32(buf, len, debug);
        ConvU32ToU8(u32, u8);
    }

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

    int enc = reader.getEnc(fname);
    if(enc == TEXT_READER_NONE){
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
            cerr << "[FAILED] Could not open " << output << endl;
            return EXIT_FAILURE;
        }

        bool flag_loop = true;
        while(flag_loop){

                int len = reader.getLine(buf, BUF_SIZE);
                if(len == TEXT_READER_EOF){
                    flag_loop = false;
                    break;
                }

                string u8 = convLineToU8(buf, len, enc, flag_debug);

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

