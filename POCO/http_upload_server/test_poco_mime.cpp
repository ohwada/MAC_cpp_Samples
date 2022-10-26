/**
 *  test_mime.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <cassert>
#include "poco_server_util.hpp"

using namespace std;


/**
 *  main
 */
int main()
{
    Poco::File file1("www/index.html");
    Poco::File file2("www/baboon.png");

    std::string mime1 = get_mime(file1);
    std::string mime2 = get_mime(file2);

    std::cout << "mime1: " << mime1 << std::endl;
    std::cout << "mime2: " << mime2 << std::endl;

    assert(mime1 == "text/html");
    assert(mime2 == "image/png");

    std::cout << "successful" << std::endl;

    return 0;
}
