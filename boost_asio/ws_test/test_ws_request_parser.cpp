/**
 * test_ws_request_parser.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <cassert>
#include "../ws_server_async/ws_request_parser.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{
    string text(
"Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n");

   string expect(
"dGhlIHNhbXBsZSBub25jZQ==");

    auto seckey = parse_seckey( text );

    cout << "seckey: " << seckey << endl;

    assert(seckey == expect);

    cout << "successful" << endl;

    return 0;
}

