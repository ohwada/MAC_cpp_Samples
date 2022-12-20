/**
 * random_int.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

 using namespace std;

/**
 * main
 */
int main()
{
  
   const int MIN = 0;
   const int MAX = 1000;

    boost::random::random_device seed_gen;
    boost::random::mt19937 gen(seed_gen);
    boost::random::uniform_int_distribution<> dist(MIN, MAX);

    cout << MIN << " -> " << MAX << endl;
    for (int i = 0; i < 10; ++i) {
        int result = dist(gen);
        cout << result << endl;
    }

    return 0;
}


// 0 -> 1000
// 66
// 160
// 713




