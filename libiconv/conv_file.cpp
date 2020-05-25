/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */

// convert text file codeset to UTF8
// reference : https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

// TODO :
// suport utf16, utf32

#include <iostream>
#include <string>

#include "TextReader.hpp"

#include "TextEncodeConverter.hpp"

#include "parse_filename.hpp"

using namespace std;


/**
 * getInputEncode
 */
string getInputEncode(int enc)
{
    string encode = "";

    if(enc == TEXT_READER_SJIS){
        encode = TEXT_ENC_SJIS;
    }else if(enc == TEXT_READER_EUCJP){
        encode = TEXT_ENC_EUCJP;
    }else if(enc == TEXT_READER_UTF16){
        encode = TEXT_ENC_UTF16;
    }else if(enc == TEXT_READER_UTF16BE){
        encode = TEXT_ENC_UTF16BE;
    }else if(enc == TEXT_READER_UTF16LE){
        encode = TEXT_ENC_UTF16LE;
    }else if(enc == TEXT_READER_UTF32){
        encode = TEXT_ENC_UTF32;
    }else if(enc == TEXT_READER_UTF32BE){
        encode = TEXT_ENC_UTF32BE;
    }else if(enc == TEXT_READER_UTF32LE){
        encode = TEXT_ENC_UTF32LE;
    }
    return encode;
}



/*
 * main
 */
int main(int argc, char** argv)
{

    const int BUF_SIZE  = 1024;
    char* buf = new char[BUF_SIZE];

    TextReader reader;

    TextEncodeConverter converter;

    string input;
    int flag_debug = 0;

    if (argc == 3) {
        input = argv[1];
        flag_debug = atoi(argv[2]);
    }else if (argc == 2) {
        input = argv[1];
    } else {
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

    string enc = getInputEncode(enc_code);
    if(enc.empty()){
            cout << "NOT find input encode" << endl;
            return EXIT_FAILURE;
    }

    converter.setDebugPrint(flag_debug);

    ofstream ofs;

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

        string text;
        int line_count = 0;
        bool flag_loop = true;

        while(flag_loop){

            line_count++;
            int len = reader.getLine(buf, BUF_SIZE);
            if(len == TEXT_READER_EOF){
                flag_loop = false;
                break;
            }

            bool ret2 = converter.convChars(buf, len, enc, text);
            if (ret2) {
                cout <<  line_count << " : " << text << endl;
                ofs << text << endl;
            } else {
                    cout <<  line_count << " : [err]" << endl;
                    if(flag_debug){
                        converter.dumpChars(buf, len);
                    }
            }

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

