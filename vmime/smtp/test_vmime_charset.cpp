/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for utf8_to_iso2022jp()
// g++ smtp/test_vmime_charset.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include <fstream>
#include <string>
#include "vmime_charset.hpp"


using namespace std;



/**
 * writeTextFile
 */
bool writeTextFile(std::string file, std::string data)
{
    std::ofstream ofs(file);
    if(!ofs){
        return false;
    }

    ofs << data;
    ofs.close();

    return true;
}


/**
 * main
 */
int main(void)
{

    string text1 = u8"テスト我輩は猫である";
    string iso2022;
    utf8_to_iso2022jp(text1, iso2022);

    string text2;
    iso2022jp_to_utf8(iso2022, text2);

    cout << "text1: " << text1 << endl;
    cout << "text2: " << text2 << endl;

    string file = "test_iso2022jp.txt";
    bool ret = writeTextFile(file, iso2022);
    if(ret){
        cout << "saved to: " << file << endl;
    } else {
        cout << "writeTextFile faild: " << file << endl;
    }

    return 0;
}

