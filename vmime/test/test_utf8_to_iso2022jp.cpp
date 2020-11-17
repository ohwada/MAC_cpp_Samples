/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for vmime_charset.hpp and utf8_to_iso2022jp()

// g++ test_utf8_to_iso2022jp.cpp -std=c++11 `pkg-config --cflags --libs vmime`

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

    string file_utf8 = "data/charset_utf8.txt";
    string file_iso2022 = "text_iso2022jp.txt";

    string text_utf8;
    string text_iso2022;

    bool ret1 = readTextFile( file_utf8, text_utf8 );

    if(!ret1){
        cout << "readTextFile faild: " << file_utf8 << endl;
	    return EXIT_FAILURE;
    }

    utf8_to_iso2022jp(text_utf8, text_iso2022);

    bool ret2 = writeTextFile(file_iso2022, text_iso2022);

    if(ret2){
        cout << "saved to: " << file_iso2022 << endl;
    } else {
        cout << "writeTextFile faild: " << file_iso2022 << endl;
    }

    return EXIT_SUCCESS;
}


// saved to: text_iso2022jp.txt

