/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// sample for Bit Generators and Distribution Functions
// display rundom number
// reference : https://abseil.io/docs/cpp/guides/random

#include <iostream>
#include "absl/random/random.h"

using namespace std;


/**
 * main
 */
int main(void)
{

    absl::BitGen bitgen;
    double fraction = absl::Uniform(bitgen, 0, 1.0);
    bool coin_flip = absl::Bernoulli(bitgen, 0.5);

    cout << "fraction: " << fraction  << endl;
    cout << std::boolalpha << "coin_flip: " << coin_flip  << endl;
    cout << "random: 100 -> 999 "<< endl;

    for(int i=0; i< 10; i++){
        int rand = absl::Uniform(bitgen, 100, 999);
        cout << rand  << endl;
    }

    return 0;
}


// fraction: 0.636696
// coin_flip: false
// random: 100 -> 999 
// 390
// 496
// 293
// 972
// 348
// 716
// 867
// 935
// 648
// 560
