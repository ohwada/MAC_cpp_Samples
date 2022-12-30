/**
 * test_ws_client_frame_builder.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "../ws_client_async/ws_client_frame_builder.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    std::string text("Hello, world!"); 

    int close_code = CLOSE_NORMAL;

    size_t expect_size1 = text.size() + 6;

    size_t expect_size2 = 8;

    std::vector<char> expect1{ (char)0x81, (char)0x8d };

        std::vector<char>  expect2{ (char)0x88, (char)0x82 };


// build text
{
    cout << "build text: " << text << endl;
 
    auto data1 = build_client_text(text);

    auto data_size = data1.size();

    cout << "data_size1: " << data_size << endl;

     dump_vec( data1);

   vector<char> sub{ data1[0], data1[1]};

    assert( data_size == expect_size1);

    assert( sub == expect1);

}

// build close
{
    cout << "build close: " << close_code << endl;

    auto data2 = build_client_close( close_code, "");

    auto data_size = data2.size();

    cout << "data_size2: " << data_size << endl;

    dump_vec(data2);

   vector<char> sub{ data2[0], data2[1]};

    assert(data_size == expect_size2);

    assert( sub == expect2);

}

    cout << "successful" << endl;

    return 0;
}

