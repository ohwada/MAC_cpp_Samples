/**
 * save_file.cpp
 * 2022-06-01 K.OHWADA
 */

// This is a simple example of saving XML document to file 
// original : https://pugixml.org/docs/quickstart.html

// g++  save_file.cpp `pkg-config --cflags --libs  pugixml` -o save

#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
    // get a test document
    pugi::xml_document doc;
    doc.load_string("<foo bar='baz'>hey</foo>");

    // tag::code[]
    // save document to file
    std::cout << "Saving result: " << doc.save_file("save_file_output.xml") << std::endl;
    // end::code[]
    return 0;
}


