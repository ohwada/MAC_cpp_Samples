/**
 *   seed_seq.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ seed_seq.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/random/seed_seq.html

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <random>


/**
 *  main
 */
int main()
{
// prepare the seeds for the size of 
// the pseudo-random number generator's state sequence
  std::array<
    std::seed_seq::result_type,
    std::mt19937::state_size
  > seed_data;

  std::random_device seed_gen;
  std::generate(seed_data.begin(), seed_data.end(), std::ref(seed_gen));

  std::seed_seq seq(seed_data.begin(), seed_data.end());


// build a seed column with non-deterministic random numbers
  std::mt19937 engine(seq);

// generate random number 
  for (int i = 0; i < 10; ++i) {
    std::uint32_t result = engine();
    std::cout << result << std::endl;
  } // for

    return 0;
}

// 1625292258
// 251724565
// 3108841704