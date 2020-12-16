/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// display program's execution tiime

// reference : https://www.boost.org/doc/libs/1_49_0/doc/html/chrono/users_guide.html


#include <iostream>
#include <boost/chrono.hpp>
#include <cmath>

int main(void)
{
    boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();

    for ( long i = 0; i < 10000000; ++i )
    std::sqrt( 123.456L ); // burn some time

    boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - start;
    std::cout << "took " << sec.count() << " seconds\n";
    return 0;
}


// took 0.053989 seconds

