/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// format string like sprintf
// https://abseil.io/docs/cpp/guides/format

#include <iostream>
#include "absl/strings/str_format.h"

using namespace std;


/**
 * main
 */
int main(void)
{

    constexpr absl::string_view FORMAT = "Welcome to %s, Number %d!";

    string str = absl::StrFormat(FORMAT, "The Village", 6);

    cout << str << endl;

    return 0;
}

// Welcome to The Village, Number 6!
