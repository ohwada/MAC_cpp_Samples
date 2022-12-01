/**
 * test_bese64.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://sanichi999.hateblo.jp/entry/2014/12/06/154356

#include <iostream>
#include <cassert>
#include "base64.hpp"


/**
 * dump_vec
 */
void dump_vec(std::string name, std::vector<char> vec)
{
    std::cout << name << ": ";
    for(auto v: vec) {
        std::cout << v << ", ";
    } // for
    std::cout << std::endl;
}

using namespace std;


/**
 * main
 */
int main() 
{
    vector<char> vec = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };

    string expect("YWJjZGVmZw");

    dump_vec("vec", vec);

    auto enc = encode_base64(vec);

    cout << "enc: " << enc << endl;

    auto dec = decode_base64(enc);

    dump_vec("dec", dec);

    assert(enc == expect);
    assert(dec == vec);

    cout << "successful" << endl;

    return 0;
}

// successful
