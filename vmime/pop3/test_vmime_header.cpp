/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for decode_header()
// g++ pop3/test_vmime_header.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include <string>
#include "vmime_header.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const string LF = "\n";

    string subject_ascii( "this is test" );

// "テスト abcedfg あいうえお"
    string subject_utf8( "=?UTF-8?B?44OG44K544OIIGFiY2VkZmcg44GC44GE44GG44GI44GK?=" );

// "テスト wxyz かきくけこ"
    string subject_iso2022jp =
    string( "=?ISO-2022-JP?B?GyRCJUYbKEIbJEIlORsoQhskQiVIGyhCIHd4eXogGyRCJCsbKEI=?=" ) +LF
    + string( "=?ISO-2022-JP?B?GyRCJC0bKEIbJEIkLxsoQhskQiQxGyhCGyRCJDMbKEI=?=" );

    string result_ascii;
    decode_header( subject_ascii, result_ascii );

    string result_utf8;
    decode_header( subject_utf8, result_utf8 );

    string result_iso2022jp;
    decode_header( subject_iso2022jp, result_iso2022jp );

    cout << "ascii: " << result_ascii << endl;
    cout << "utf8: " << result_utf8 << endl;
    cout << "iso2022jp: " << result_iso2022jp << endl;

    return 0;
}


// ascii: this is test
// utf8: テスト abcedfg あいうえお
// iso2022jp: テスト wxyz かきくけこ

