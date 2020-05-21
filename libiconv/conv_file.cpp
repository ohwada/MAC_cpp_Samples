/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */

// convert text file codeset to UTF8
// reference : https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

// TODO:
// sjis, eucjp, utf16be, utf32be : good
// utf16le, utf16, utf32le, utf32 : not working properly
// sample_utf16le.txt :
//[Err] iconv :  EINVAL ( 22 ) left( 1 , 1017 ) 

#include <iostream>
#include <string>

#include "TextEncodeConverter.hpp"

#include "parse_filename.hpp"

using namespace std;


/**
 * getInputEncode
 */
string getInputEncode(string filename, int *flag_utf)
{
    string encode = "";
    string parse_encode = "";
    int pos  = filename.find_last_of('_');
    if (pos != std::string::npos) {
        parse_encode = filename.substr(pos+1, filename.size()-pos);
    }

int utf = 0;
    if(parse_encode == "sjis"){
        encode = TEXT_ENC_SJIS;
    }else if(parse_encode == "eucjp"){
        encode = TEXT_ENC_EUCJP;
    }else if(parse_encode == "utf16"){
        encode = TEXT_ENC_UTF16;
    }else if(parse_encode == "utf16be"){
        encode = TEXT_ENC_UTF16BE;
        utf = 1;
    }else if(parse_encode == "utf16le"){
        encode = TEXT_ENC_UTF16LE;
    }else if(parse_encode == "utf32"){
        encode = TEXT_ENC_UTF32;
    }else if(parse_encode == "utf32be"){
        encode = TEXT_ENC_UTF32BE;
        utf = 2;
    }else if(parse_encode == "utf32le"){
        encode = TEXT_ENC_UTF32LE;
    }
    *flag_utf = utf; 
    return encode;
}



/*
 * main
 */
int main(int argc, char** argv)
{

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

    int flag_utf;
    string enc_in = getInputEncode(fname, &flag_utf);
    if(enc_in.empty()){
            cout << "NOT find input encode" << endl;
            return EXIT_FAILURE;
    }

    cout << " input encode: " << enc_in << endl;

    converter.setDebugPrint(flag_debug);

   int ret = converter.convFile(input, enc_in, output, flag_utf);
    if (ret == TEXT_ENC_RET_SUCCESS) {
            cout << "conv SUCCESS!" << endl;
    } else if (ret == TEXT_ENC_RET_ERR) {
            cout << "conv error"  << endl;
    } else {
            cout << "conv FAILED!"  << endl;
            return EXIT_FAILURE;
    }

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

