/**
 * save_stream.cpp
 * 2022-06-01 K.OHWADA
 */

// This is a simple example of saving XML document to standard output
// original : https://pugixml.org/docs/quickstart.html

// g++  save_stream.cpp `pkg-config --cflags --libs  pugixml` -o save_stream

#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
    // get a test document
    pugi::xml_document doc;
    doc.load_string("<foo bar='baz'><call>hey</call></foo>");

    // tag::code[]
    // save document to standard output
    std::cout << "Document:\n";
    doc.save(std::cout);
    // end::code[]
    return 0;
}


