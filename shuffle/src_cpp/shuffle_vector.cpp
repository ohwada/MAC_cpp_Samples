/**
 * shuffle sample
 * 2020-03-01 K.OHWADA
 */

// shuffle int vector with mt19937
// reference : https://en.cppreference.com/w/cpp/algorithm/random_shuffle


#include<iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>


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

    random_device rd;
    mt19937 mt(rd());
    
    shuffle( vec.begin(), vec.end(),  mt );

	cout << " \n after: " << endl;
	dump(vec);

// before shufle
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
// after shufle
//0, 2, 3, 8, 7, 9, 6, 4, 1, 5, 

    return 0;
}