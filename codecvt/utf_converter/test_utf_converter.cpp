 /**
 * utf converter Sample
 * 2020-03-01 K.OHWADA
 */


// convert text codeset to UTF-8 with utf_converter

#include <string>
#include <iostream>

#include "utf_converter.hpp"

#include "../samples/sample_utf.h"

using namespace std;


/**
 * main
 */
int main( int argc, char **argv )
{

    u16string u16 = (char16_t *)SAMPLE_UTF16BE;

    cout  << "test_utf_converter.cpp"  << endl;

    string u8;

    ConvU16ToU8(u16, u8);

    cout << "utf16 to utf8: " << u8 << endl;


    u32string u32 = (char32_t *)SAMPLE_UTF32BE;

    string u8_2;

    ConvU32ToU8(u32, u8_2);

    cout << "utf32 to utf8: " << u8_2 << endl;

    return EXIT_SUCCESS;

}
