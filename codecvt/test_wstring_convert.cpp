/**
 * codecvt Sample
 * 2020-03-01 K.OHWADA
 */

// convert UTF-8 to/from UTF-16
// reference : https:// ja.cppreference.com/w/cpp/locale/codecvt_utf8_utf16

// Note:
// codecvt is deprecated from c ++ 17

#include <string>
#include <iostream>
#include <codecvt>

#include "sample_utf.h"

using namespace std;


/**
 * main
 */
int main( int argc, char **argv )
{

    string u8 = (char *)SAMPLE_UTF8;
    u16string u16 = (char16_t *)SAMPLE_UTF16BE;

    cout  << "test_wstring_convert.cpp"  << endl;

    string u8_conv = std::wstring_convert<
        codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);

    cout << "utf16 to utf8: " << u8_conv << endl;


    u16string u16_conv = wstring_convert<
        codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(u8);

    if(u16 != u16_conv){
        cout << "utf8 to utf16 Faild " << endl;
    }

    cout << "utf8 to utf16: " << endl;
    for (char16_t c : u16_conv) {
            cout << hex << showbase << c << ' ';
    } // for
    cout << endl;
    
    return EXIT_SUCCESS;
}

