/**
 * test_ws_server_frame_builder.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "../ws_server_async/ws_server_frame_builder.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string text("Hello, world!"); 

    int close_code = CLOSE_NORMAL;

    vector<char> expect1{ (char)0x81, 0x0d, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21};

       vector<char> expect2{ (char)0x88, 0x02, 0x03, (char)0xe8 };

// build text
{
    cout << "build text: " << text << endl;

    auto data1 = build_server_text(text);

    dump_vec(data1);

    assert(data1 == expect1);
}

// build close
{
    cout << endl;
    cout << "build close: " <<  close_code << endl;

    auto data2 = build_server_close( close_code, "" );

    dump_vec(data2);

    assert(data2 == expect2);
}

    cout << "successful" << endl;

    return 0;
}

