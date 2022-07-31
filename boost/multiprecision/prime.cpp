/**
 * prime.cpp
* prime numbers up to 100
 * 2022-06-01 K.OHWADA
 */

// g++ prime.cpp -std=c++11

// reference : https://faithandbrave.hateblo.jp/entry/20130222/1361516978

#include <iostream>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace mp = boost::multiprecision;


/**
 * main
 */
int main()
{
    int sum = 0;
    boost::random::mt19937 gen;

// prime numbers up to 100
    for (int i = 2; i < 100; ++i) 
    {
        bool is_prime = mp::miller_rabin_test(i, 25, gen);
        if(is_prime){
            std::cout << i << std::endl;
            sum ++;
        }
    } // for

    std::cout << "sum=" << sum << std::endl;
    return 0;
}


// 2
// 3
// 5
// sum=25



