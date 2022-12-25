/**
 * ws_tool.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <vector>
#include "boost_util.hpp"
#include "ws_frame_parser.h"


/**
 * dump_vec
 */
void dump_vec(std::vector<char> vec)
{
    dump_frame_data( (char *)vec.data(),  vec.size());
}


/**
 * parse_data
 */
void parse_data(std::string text)
{

    auto hex = str_replase_all(text);

    std::cout << hex << std::endl;

    auto vec = hex2bin(hex);

    dump_vec(vec);

    parse_frame( (char *)vec.data(), vec.size() );
}

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

// tcpdump data
    string text("818d b636 a1ed fe53 cd81 d91a 819a d944 cd89 97");

    parse_data(text);


    string str;

    cout << "input data" << endl;

    for(int i=0; i<10; i++)
    {
        cout << ">";
        if (std::getline(std::cin, str)) {
            if( str.size() == 0){
                break;
            }
            parse_data(str);
        }
    }// for

    return 0;
}

