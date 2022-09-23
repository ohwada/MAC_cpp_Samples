/**
 *  parse_url.cpp
 * 2020-07-01 K.OHWADA
 */


// https://github.com/nekipelov/httpparser

#include <iostream>
#include <httpparser/urlparser.h>

using namespace httpparser;


/**
 *  main
 */
int main(int, char**)
{
    UrlParser parser;

    {
        const char url[] = "git+ssh://example.com/path/file";

        if( parser.parse(url) )
            std::cout << parser.scheme() << "://" << parser.hostname() << std::endl;
        else
            std::cerr << "Can't parse url: " << url << std::endl;
    }

    {
        const char url[] = "https://example.com/path/file";

        if( parser.parse(url) )
            std::cout << parser.scheme() << "://" << parser.hostname() << std::endl;
        else
            std::cerr << "Can't parse url: " << url << std::endl;
    }

    return EXIT_SUCCESS;
}
