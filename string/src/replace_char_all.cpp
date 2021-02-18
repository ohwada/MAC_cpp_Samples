/**
 * C++ string sample
 * 2021-02-01 K.OHWADA
 */

// replace all characters in a string

//https://marycore.jp/prog/cpp/std-string-replace-first-all/#std%3A%3Areplace%E9%96%A2%E6%95%B0%E3%81%AB%E3%82%88%E3%82%8B%E5%85%A8%E7%BD%AE%E6%8F%9B

#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

/**
 *  main
 */
int main(void) 
{

    const string src("ABCDEFGAabcdefgaAdDAW");

    const char TARGET = 'A';

    const char REPLACE = '_';

	cout << src << endl; 

	string str = src;

    std::replace( str.begin(), str.end(), TARGET, REPLACE );

	cout << str << endl; 

	return EXIT_SUCCESS;

}

