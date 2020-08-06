/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// random shufle int vector
// reference ; https://cpprefjp.github.io/reference/algorithm/random_shuffle.html
// Note:
// std::random shufle
// deprecated in C++14
// removed in C++17
// recommend std::shuffle

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;


/**
 * dump
 */
void dump(vector<int> vec) {

    for(auto x: vec) {
        cout << x << ", ";
    } 
    cout << endl;

}


/**
 * main
 */
int main(int argc, char *argv[])
{

// generate values ​​from 0 to 9
 	vector<int> vec(10);
	iota(vec.begin(), vec.end(), 0);

	cout << "before: " << endl;
	dump(vec);
	
	random_shuffle(vec.begin(), vec.end());

	cout << "\n after: " << endl;
	dump(vec);

// before: 
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
//  after: 
// 6, 0, 3, 5, 7, 8, 4, 1, 2, 9, 

	return 0;
}
