/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for vmime_charset.hpp and iso2022jp_to_utf8()

// g++ test_iso2022jp_to_utf8.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include <fstream>
#include <string>
#include "../pop3/vmime_charset.hpp"
#include "../pop3/file_util.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    string file_iso2022 = "data/charset_iso2022jp.txt";
    string file_utf8 = "text_utf8.txt";

    string text_utf8;
    string text_iso2022;

    bool ret1 = readTextFile( file_iso2022, text_iso2022 );

    if(!ret1){
        cout << "readTextFile faild: " << file_iso2022 << endl;
	    return EXIT_FAILURE;
    }

    iso2022jp_to_utf8(text_iso2022, text_utf8);

// display
    cout << text_utf8 << endl;

    bool ret2 = writeTextFile(file_utf8, text_utf8);

    if(ret2){
        cout << "saved to: " << file_utf8 << endl;
    } else {
        cout << "writeTextFile faild: " << file_utf8 << endl;
    }

    return EXIT_SUCCESS;
}


// saved to: test_utf8.txt

