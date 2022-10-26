/**
 * test_response_parser.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "response_parser.hpp"
#include "file_util.hpp"
#include "save.hpp"


using namespace std;


int main()
{

    string file("sample/sample_google_response.txt");

    string text1("5e29\r\n<html>abcdefghijklmnopqr\r\nstuvwxyz\r\n0\r\n");

    string chunk_size;
    string slim_body;

cout << "test parse_chunked_body" << endl;

    bool ret1 = parse_chunked_body(text1,  chunk_size, slim_body);
    if(!ret1){
        cerr<< "cannot parse_chunked_bod : " << text1 << endl;
    }

    cout << endl;
    cout << "chunk size: " << chunk_size << endl;

    cout << endl;
    cout << "slim body" << endl;
    cout << slim_body << endl;

    size_t slim_body_size = slim_body.size();
    cout << "slim body size: " << slim_body_size << endl;
 
    string expect1("5e29");

    assert( chunk_size == expect1);

     assert( slim_body_size == 36);


cout << "test response" << endl;

    string response;

    bool ret2 = readBinaryFile2(file, response);
    if(!ret2){
        cerr<< "cannot readBinaryFile: " << file << endl;
    }


    cout << endl;
    cout << "response size" << response.size() << endl;
    // cout << response << endl;

    string header;
    string response_body;

    bool ret3 = split_header_body(response, header, response_body);
    if(!ret3){
        cerr<< "split_header_body" << endl;
    }

    cout << endl;
    cout << "header" << endl;
    cout << header << endl;

    cout << endl;
    cout << "response body size" << response_body.size() << endl;
    // cout << response_body << endl;

    bool is_chunked = is_transfer_encoding_chunked(header);

    cout  << std::boolalpha << "is_chunked: " << is_chunked << endl;

    bool ret4 = parse_chunked_body(response_body,  chunk_size, slim_body);
    if(!ret4){
        cerr<< "cannot parse_chunked_body" << endl;
    }

    cout << endl;
    cout << "chunk size: " << chunk_size << endl;

    cout << endl;
    // cout << "body" << endl;
    // cout << body << endl;

    slim_body_size = slim_body.size();
    cout << "slim body size: " << slim_body_size << endl;

    string expect2("5f3e");

     assert( chunk_size == expect2);

     assert( slim_body_size == 54301);

    bool is_save_verbose = true;

    save_body(slim_body,  is_save_verbose);


    cout<< "successful" << endl;

    return 0;
}


