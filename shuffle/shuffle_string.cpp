/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// shufle char in stringwith mt19937
// reference : https://cpprefjp.github.io/reference/algorithm/shuffle.html

#include <iostream>
#include <string>
#include <random>


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    string str1 = "0123456789";
    string str2 = "abcdefghij";

     random_device rd;
    mt19937 mt(rd());

    cout << "before: "  << str1 << endl;

  shuffle(str1.begin(), str1.end(), mt);

    cout << " after: "<< str1 << endl;

    cout << endl;
    cout << "before: " << str2 << endl;

  shuffle(str2.begin(), str2.end(), mt);

    cout <<  " after: " << str2 << endl;

// before: 0123456789
//    after: 5641390278
//
// before: abcdefghij
//    after: hbgejdicaf


    return 0;
}
