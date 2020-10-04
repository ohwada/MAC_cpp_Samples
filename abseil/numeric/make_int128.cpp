/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// sample for MakeInt128
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

int64_t a = LLONG_MAX;

// Implicit conversion from int64_t OK
absl::int128 v = a;

// Error: Implicit conversion to int64_t not OK
// int64_t b = v;

// Explicit conversion to int64_t OK
int64_t i = static_cast<int64_t>(v);

cout << hex << "int64: " << a << endl;
cout << hex << "int128: " << v << endl;
cout << hex << "cast int64: " << i << endl;

// Construct a value of 2^64
absl::int128 big = absl::MakeInt128(1, 0);

// Get the high and low 64 bits of an int128
int64_t high = absl::Int128High64(v);
uint64_t low = absl::Int128Low64(v);


cout << hex << "big: " << v << endl;
cout << hex << "high: " << high << endl;
cout << hex << " low: " << low << endl;

return 0;
}


// int64: 7fffffffffffffff
// int128: 7fffffffffffffff
// cast int64: 7fffffffffffffff
// big: 7fffffffffffffff
// high: 0
// low: 7fffffffffffffff

