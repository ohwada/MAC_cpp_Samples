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
    string req1("/");

    string req2("?name=taro");

   string req3("?id=123");

    string key1;
   string value1;
    parse_request(req1,  key1, value1);

    cout << key1 << endl;
    cout << value1 << endl;

    string key2;
   string value2;
    parse_request(req2,  key2, value2);

    cout << key2 << endl;
    cout << value2 << endl;

    string key3;
   string value3;
    parse_request(req3,  key3, value3);

    cout << key3 << endl;
    cout << value3 << endl;

    cout << "successful" << endl;

    return 0;
}
