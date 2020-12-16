/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// parse command options

// reference : https://www.boost.org/doc/libs/1_62_0/libs/program_options/example/first.cpp

// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;


/**
 * main
 */
int main(int ac, char* av[])
{

    try {

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<double>(), "set compression level")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            cout << desc << "\n";
            return EXIT_SUCCESS;
        }


        if (vm.count("compression")) {
            cout << "Compression level was set to " 
                 << vm["compression"].as<double>() << ".\n";
        } else {
            cout << "Compression level was not set.\n";
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return  EXIT_FAILURE;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return EXIT_SUCCESS;
}


// Compression level was not set.


// % ./a.out --help
// Allowed options:
//  --help                produce help message
//  --compression arg     set compression level


