/**
 * traverse_iter.cpp
 * 2022-06-01 K.OHWADA
 */

// Here is an example of using iterators for document traversal
// original : https://pugixml.org/docs/quickstart.html

// g++  traverse_iter.cpp `pkg-config --cflags --libs  pugixml` -o iter

#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
    pugi::xml_document doc;
    if (!doc.load_file("xgconsole.xml")) return -1;

    pugi::xml_node tools = doc.child("Profile").child("Tools");

    // tag::code[]
    for (pugi::xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
    {
        std::cout << "Tool:";

        for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
        {
            std::cout << " " << ait->name() << "=" << ait->value();
        }

        std::cout << std::endl;
    }
    // end::code[]
    return 0;
}

