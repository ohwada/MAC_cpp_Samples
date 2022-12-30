/**
 * test_gen_accept_key.cpp
 * 2022-10-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <cassert>

#include "../ws_server_async/ws_response_builder.hpp"

 using namespace std;


/**
 * main
 */
int main()
{

    string seckey(
"dGhlIHNhbXBsZSBub25jZQ==");

    string expect(
"s3pPLMBiTxaQ9kYGzzhZRbK+xOo="); 

     auto accept_key = gen_accept_key(seckey);

    cout << "accept_key: " << accept_key << endl;

    assert( accept_key == expect);

    cout << "successful" << endl;

    return 0;
}


