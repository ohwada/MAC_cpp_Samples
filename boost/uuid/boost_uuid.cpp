/**
 * boost_uuid.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ boost_uuid.cpp -o boost_uuid
// reference : https://boostjp.github.io/tips/uuid.html

#include <iostream>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::uuids;


/**
 * main
 */
int main()
{
// generate uuid
    const uuid id = random_generator()();

// convert to string
    const std::string result = boost::lexical_cast<std::string>(id);

    std::cout << result << std::endl;

    return 0;
}

