/**
 *  parse_width.cpp
 * 2022-06-01 K.OHWADA
 */

// A parser for a single option
// width :  -w 123
// reference : https://github.com/catchorg/Clara

#include <iostream>
#include "clara.hpp"


/**
 *  parse_width
 */
int parse_width(int argc, char* argv[])
{

using namespace clara;

    int width = 0;

    auto cli
    = Opt( width, "width" )
        ["-w"]["--width"]
        ("How wide should it be?");

    auto result = cli.parse( Args( argc, argv ) );
    if( !result ) {
        std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
        return -1;
    }

    return width;
}

using namespace std; 


/**
 *  main
 */
int main(int argc, char* argv[])
{

    int width = parse_width(argc, argv);

    cout << "width: " << width << endl;

    return 0;
}

