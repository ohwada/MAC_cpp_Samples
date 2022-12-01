/**
 * test_hex.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://faithandbrave.hateblo.jp/entry/20120706/1341558540

#include <iostream>
#include <cstdio>
#include <cassert>
#include "hex.hpp"


/**
 *  dump_vec
 */
void dump_vec(std::string name, std::vector<char> vec)
{
    printf("%s: ", name.c_str() );
    for(char  x: vec) {
        printf("%02x, ",  (unsigned char)x);
    }
    printf("\n");

}


using namespace std;


/**
 * main
 */
int main()
{
    vector<char> bin1 = { 0x01, 0x02, 0x03, 0x04, 0x05,0x06, 0x07, 0x08, 0x09 };

    dump_vec("bin1", bin1);

    auto hex = bin2hex(bin1);

    cout << "hex: " << hex << endl;

    auto bin2 = hex2bin(hex);

    dump_vec("bin2", bin2);

    assert(bin1 == bin2);

    cout << "successful" << endl;

    return 0;
}

