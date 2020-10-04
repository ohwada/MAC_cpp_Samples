/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

 // sample for MakeUint128
// https://abseil.io/docs/cpp/guides/numeric

#include <iostream>
#include <climits>
#include "absl/numeric/int128.h"

using namespace std;


/**
 * main
 */
int main(void)
{

uint64_t a = ULLONG_MAX;

// Implicit conversion from uint64_t OK
absl::uint128 v = a;

// Error: Implicit conversion to uint64_t not OK
//uint64_t b = v;

// Explicit conversion to uint64_t OK
uint64_t i = static_cast<uint64_t>(v);

cout << hex << "uint64 : " << a << endl; 
cout << hex << "uint128 : " << v << endl; 
cout << hex << "cast uint64 : " << i << endl; 

// Construct a value of 2^64
absl::uint128 big = absl::MakeUint128(1, 0);

// Get the high and low 64 bits of a uint128
uint64_t high = absl::Uint128High64(v);
uint64_t low = absl::Uint128Low64(v);

cout << hex << "big : " << big << endl; 
cout << hex << "high :"  << high << endl; 
cout << hex << "low : " << low << endl; 

    return 0;
}


// uint64 : ffffffffffffffff
// uint128 : ffffffffffffffff
// cast uint64 : ffffffffffffffff
// big : 10000000000000000
// high :0
// low : ffffffffffffffff
