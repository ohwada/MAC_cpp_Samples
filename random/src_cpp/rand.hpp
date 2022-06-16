#pragma once
/**
 * C++ sample
 * 2022-06-01 K.OHWADA
 */

// generate random integer using mt19937
// reference : ://vivi.dyndns.org/tech/cpp/random.html

#include <random>

// prototype
int genRandInt(int min, int max);
double genRandReal(double min, double max);


// initialization
std::random_device rd;
std::mt19937 mt(rd());


/**
 * genRandInt
 */
int genRandInt(int min, int max)
{
    std::uniform_int_distribution<> rand_int(min,  max);
    return rand_int(mt);
}


/**
 * genRandReal
 */
double genRandReal(double min, double max)
{
    std::uniform_real_distribution<double>rand_real(min,  max);
    return rand_real(mt);
}

