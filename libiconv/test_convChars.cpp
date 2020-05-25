/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */

// convert codeset to UTF-8
#include <string>
#include <iostream>

#include "./samples/sample_enc.h"

#include "TextEncodeConverter.hpp"

using namespace std;


/*
 * main
 */
int main(int argc, char** argv)
{

    TextEncodeConverter converter;

    string ver = converter.getLibiconvVersion();
    cout << "libiconv Version: " << ver << endl;

    converter.setDebugPrint(true);

    string expect_utf8 = (char *)EXPECT_UTF8;

    cout << "expect: " << expect_utf8 << endl;

    string text_sjis;
    converter.convChars(
        (char *)SAMPLE_SJIS, 
        SAMPLE_SJIS_SIZE, 
        TEXT_ENC_SJIS,
        text_sjis);

    if(text_sjis != expect_utf8){
        cout << "[Err] sjis: not match expect value"  << endl;
    }

     cout << "sjis: " << text_sjis << endl;

    string text_euc;
    converter.convChars(
        (char *)SAMPLE_EUCJP, 
        SAMPLE_EUCJP_SIZE, 
        TEXT_ENC_EUCJP,
        text_euc);

    if(text_euc != expect_utf8){
        cout << "[Err] euc: not match expect value"  << endl;
    }

     cout << "euc: " << text_euc << endl;

    string text_utf16be;
    converter.convChars(
        (char *)SAMPLE_UTF16BE, 
        SAMPLE_UTF16BE_SIZE, 
        TEXT_ENC_UTF16BE,
        text_utf16be);

    if(text_utf16be != expect_utf8){
        cout << "[Err] utf16be: not match expect value"  << endl;
    }

     cout << "utf16be: " << text_utf16be << endl;

    string text_utf16le;
    converter.convChars(
        (char *)SAMPLE_UTF16LE, 
        SAMPLE_UTF16LE_SIZE, 
        TEXT_ENC_UTF16LE,
        text_utf16le);

    if(text_utf16le != expect_utf8){
        cout << "[Err] utf16le: not match expect value"  << endl;
    }

     cout << "utf16be: " << text_utf16be << endl;

    string text_utf16bom;
    converter.convChars(
        (char *)SAMPLE_UTF16BOM, 
        SAMPLE_UTF16BOM_SIZE, 
        TEXT_ENC_UTF16,
        text_utf16bom);

    if(text_utf16bom != expect_utf8){
        cout << "[Err] utf16bom: not match expect value"  << endl;
    }

     cout << "utf16bom: " << text_utf16bom << endl;

    string text_utf32be;
    converter.convChars(
        (char *)SAMPLE_UTF32BE, 
        SAMPLE_UTF32BE_SIZE, 
        TEXT_ENC_UTF32BE,
        text_utf32be);

    if(text_utf32be != expect_utf8){
        cout << "[Err] utf32be: not match expect value"  << endl;
    }

     cout << "utf32be: " << text_utf32be << endl;

// sample : nclude 0
    string text_utf16be_2;
    converter.convChars(
        (char *)SAMPLE_UTF16BE_2, 
        SAMPLE_UTF16BE_2_SIZE, 
        TEXT_ENC_UTF16BE,
        text_utf16be_2);

     cout << "utf16be 2: " << text_utf16be_2 << endl;

    string text_utf16le_2;
    converter.convChars(
        (char *)SAMPLE_UTF16LE_2, 
        SAMPLE_UTF16LE_2_SIZE, 
        TEXT_ENC_UTF16LE,
        text_utf16le_2);

     cout << "utf16le 2: " << text_utf16le_2 << endl;

    cout << "convert end" << endl;

    return EXIT_SUCCESS;
}

