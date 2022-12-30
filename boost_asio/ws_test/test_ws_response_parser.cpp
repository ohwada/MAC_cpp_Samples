/**
 * test_ws_request_parser.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <cassert>
#include "../ws_client_async/ws_response_parser.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{
    string text1(
"HTTP/1.1 101 Switching Protocols\r\n");

    string text2(
"Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=\r\n");

   string expect1("101");

   string expect2(
"s3pPLMBiTxaQ9kYGzzhZRbK+xOo=");

    auto code = parse_status_code( text1 );

    cout << "status code: " << code << endl;


    auto key = parse_accept_key( text2 );

    cout << "accept_key: " << key << endl;

    assert(code == expect1);

    assert(key == expect2);

    cout << "successful" << endl;

    return 0;
}

