/**
 * test_ws_frame_parser.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "../ws_server_async/ws_frame_parser.hpp"


 using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

  vector<char> data1{ (char)0x81, (char)0x8d, (char)0xb6, 0x36, (char)0xa1, (char)0xed, (char)0xfe, (char)0x53, (char)0xcd, (char)0x81, (char)0xd9, (char)0x1a, (char)0x81, (char)0x9a, (char)0xd9, 0x44, (char)0xcd, (char)0x89, (char)0x97};

 vector<char> data2{ (char)0x81, (char)0x0d, (char)0x48, (char)0x65, (char)0x6c, (char)0x6c, (char)0x6f, (char)0x2c, 0x20, (char)0x77, (char)0x6f, (char)0x72, (char)0x6c, (char)0x64, (char)0x21};

vector<char> data3{(char)0x88, (char)0x82, (char)0x67, (char)0x3a, (char)0x0f, (char)0x22, (char)0x64, (char)0xd2};

vector<char> data4{ (char)0x88, (char)0x02, (char)0x03, (char)0xe8 };


    string expect("Hello, world!"); 

    int expect_code = 1000;

// data1
{
    cout << "data1" << endl;

    string text1;

    parse_text( data1.data(),  data1.size(), text1);

    cout << "text1: " << text1 << endl;

    assert(text1 == expect);
}

// data2
{
    cout << endl;
    cout << "data" << endl;

    string text2;

    parse_text( data2.data(),  data2.size(), text2);
   
    cout << "text2: " << text2 << endl;

    assert( text2 == expect);
}

// data3
{
    cout << endl;
    cout << "data3"<< endl;

    int closecode3;
    std::string reason3;

    parse_close( data3.data(),  data3.size(), closecode3, reason3);

    auto str_close = close_to_string( closecode3 , reason3 );

    cout << str_close << endl;
 
    assert(closecode3 == expect_code);
}


// data4
{
    cout << endl;
    cout << "data4"<< endl;

    int closecode4;
    std::string reason4;

    parse_close( data4.data(),  data4.size(), closecode4, reason4);

    auto str_close = close_to_string( closecode4 , reason4 );

    cout << str_close << endl;
 
    assert(closecode4 == expect_code);
}

    cout << endl;
    cout << "successful" << endl;

    return 0;
}

