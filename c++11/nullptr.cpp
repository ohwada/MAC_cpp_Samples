/**
 * nullptr.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ nullptr.cpp 

// reference : https://qiita.com/go_astrayer/items/6afb1592a8a5763fede1reference : 

#include <iostream>

using namespace std;


/**
 * Func
 */
void Func(int v) {
    cout << __PRETTY_FUNCTION__ << endl;
    cout << "v: " << v << endl;
}


/**
 * Func
 */
void Func(void * p) {
    cout << __PRETTY_FUNCTION__ << endl;
}


/**
 * main
 */
int main()
{
    Func(10);

// nullptr
    Func(nullptr);

// NULL is interpreted as an integer 0
    Func( (int)NULL );

    return 0;
}


