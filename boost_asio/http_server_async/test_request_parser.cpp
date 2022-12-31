/**
 * test_request_parser.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <cassert>
#include"request_parser.hpp"

using namespace std;


/**
 * main
 */
int main()
{

    string request1("GET / HTTP/1.1");
    string request2("GET /abc HTTP/1.1");

    string expect1("/");
    string expect2("/abc");

    auto path1 = parse_path(request1);

    std::cout << request1 << std::endl;

    cout<< "path1: " << path1 << endl;

    assert(path1 == expect1);

    auto path2 = parse_path(request2);

    std::cout << request2 << std::endl;

    cout<< "path2: " << path2 << endl;

    assert(path2 == expect2);

    cout << "successful" << endl;

    return 0;
}