/**
 * test_request_parser.hpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <cassert>
#include "request_parser.hpp"

using namespace std;



int main()
{
    string req1("GET / HTTP/1.1");

    string req2("GET /favicon.ico HTTP/1.1");

    string path1;
    parse_request(req1,  path1);

    cout << path1 << endl;

    string path2;
    parse_request(req2,  path2);

    cout << path2 << endl;

    assert(path1 == "/");
    assert(path2 == "/favicon.ico");

    cout << "successful" << endl;

    return 0;
}

