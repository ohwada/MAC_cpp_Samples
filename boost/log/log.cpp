/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// logging
// reference : https://faithandbrave.hateblo.jp/entry/20130725/1374736211

#define BOOST_LOG_DYN_LINK 1
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>


/**
 * main
 */
int main(void)
{

    // logging without filters
    // logging for each category
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

  
// logging with filter
// log out info and above
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );

    return EXIT_SUCCESS;
}



// [2020-12-13 20:15:31.821536] [0x0000000109d67dc0] 
// [trace]   A trace severity message
// [2020-12-13 20:15:31.822140] [0x0000000109d67dc0] 
// [debug]   A debug severity message
// [2020-12-13 20:15:31.822161] [0x0000000109d67dc0] 
// [info]    An informational severity message
// [2020-12-13 20:15:31.822170] [0x0000000109d67dc0] 
// [warning] A warning severity message
// [2020-12-13 20:15:31.822177] [0x0000000109d67dc0] 
// [error]   An error severity message
// [2020-12-13 20:15:31.822184] [0x0000000109d67dc0] 
// [fatal]   A fatal severity message

