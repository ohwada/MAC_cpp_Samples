/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// convert string  to number
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>

#include "absl/strings/numbers.h"

using namespace std;


/**
 * main
 */
int main(void) 
{

    string str_int = "123";
    string str_float = "3.14";
    string str_double = "1e2";
    string str_bool = "true";

    int out_int;
    bool ret1 = absl::SimpleAtoi(str_int, &out_int);

    float out_float;
    bool ret2 = absl::SimpleAtof(str_float, &out_float);

    double out_double;
    bool ret3 = absl::SimpleAtod(str_double, &out_double);

    bool out_bool;
    bool ret4 = absl::SimpleAtob(str_bool, &out_bool);

    cout << "'" << str_int << "' -> " << out_int << endl;

    cout<< "'" << str_float << "' -> " << out_float << endl;

    cout<< "'" << str_double << "' -> " << out_double << endl;

    cout<< "'"  << std::boolalpha << str_bool << "' -> " << out_bool << endl;

    return 0;
}


// '123' -> 123
// '3.14' -> 3.14
// '1e2' -> 100
// 'true' -> true

