/**
 * load_file.cpp
 * 2022-06-01 K.OHWADA
 */

// This is an example of loading XML document from file
// original : https://pugixml.org/docs/quickstart.html

// g++  load_file.cpp `pkg-config --cflags --libs  pugixml` -o load


#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
// tag::code[]
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("tree.xml");

    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
// end::code[]
}

