 /**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// generate random number using mt19937
// reference : ://vivi.dyndns.org/tech/cpp/random.html


#include <random>
#include <vector>

#ifndef _H_RANDOM_NUMBER_H_
#define _H_RANDOM_NUMBER_H_

// prototype
std::vector<int> gen_random_vector(int num, int min, int max);


/**
 * gen_random_vector
 */
std::vector<int> gen_random_vector(int num, int min, int max)
{

    std::random_device rd;

    std::mt19937 mt(rd());

    std::uniform_int_distribution<> rand(min,  max);

    std::vector<int> vec;
    for(int i=0; i<num; i++)
    {
        vec.push_back( rand(mt) );
    }

    return vec;
}


#endif // _H_RANDOM_NUMBER_H_
