/**
 *  test_poco_mime.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <cassert>
#include "poco_mime.hpp"

using namespace std;


/**
 *  main
 */
int main()
{
   string fpath1("www/index.html");
    string fpath2("www/baboon.png");

    Poco::File file1( fpath1);
    Poco::File file2(fpath2);

    string mime1 = get_mime(file1);
    string mime2 = get_mime(file2);

    cout << fpath1 << endl;
    cout << "mime1: " << mime1 << endl;

    cout << fpath2 << endl;
    cout << "mime2: " << mime2 << endl;

    assert(mime1 == "text/html");
    assert(mime2 == "image/png");

    cout << "successful" << endl;

    return 0;
}
