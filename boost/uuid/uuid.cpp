/**
 * uuid.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://boostjp.github.io/tips/uuid.html

#include <iostream>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

 using namespace std;
using namespace boost::uuids;


/**
 * main
 */
int main()
{
// generate uuid
    const uuid id = random_generator()();

// convert to string
    auto result = boost::lexical_cast<std::string>(id);

    cout << result << endl;

    return 0;
}

// fab81212-63a0-4718-b2f6-ae5ae9b4de69  

