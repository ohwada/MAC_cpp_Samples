/**
 * clamp.cpp
 * 2022-06-01 K.OHWADA
 */

// https://faithandbrave.hateblo.jp/entry/20120704/1341382789

#include <iostream>
#include <boost/algorithm/clamp.hpp>

using namespace std;
using boost::algorithm::clamp;


/**
 * main
 */

int main()
{

    int x1 = 11;
    int x2 = clamp(x1, 0, 10);

    int y1 = -1;
    int y2 = clamp(y1, 0, 10);

    cout << x1 <<  "-> "<< x2 << endl;
    cout << y1 <<  "-> "<< y2 << endl;

    return 0;
}

// 11-> 10
// -1-> 0

