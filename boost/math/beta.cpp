/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// computes beta function
// display Pascal's triangle

// reference : https://en.cppreference.com/w/cpp/experimental/special_functions/beta

#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>

double binom(int n, int k) { return 1/((n+1)*std::beta(n-k+1,k+1)); }

int main(void)
{
    std::cout << "Pascal's triangle:\n";
    for(int n = 1; n < 10; ++n) {
        std::cout << std::string(20-n*2, ' ');
        for(int k = 1; k < n; ++k)
            std::cout << std::setw(3) << binom(n,k) << ' ';
        std::cout << '\n';
    }
}
