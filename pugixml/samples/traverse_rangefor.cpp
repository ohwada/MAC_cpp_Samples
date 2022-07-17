/**
 * traverse_rangefor.cpp
 * 2022-06-01 K.OHWADA
 */

// Here is an example of using C++11 range-based for loop for document traversal
// original : https://pugixml.org/docs/quickstart.html

// g++ traverse_rangefor.cpp -std=c++11 `pkg-config --cflags --libs  pugixml` -o rangefor

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
    for (pugi::xml_node tool: tools.children("Tool"))
    {
        std::cout << "Tool:";

        for (pugi::xml_attribute attr: tool.attributes())
        {
            std::cout << " " << attr.name() << "=" << attr.value();
        }

        for (pugi::xml_node child: tool.children())
        {
            std::cout << ", child " << child.name();
        }

        std::cout << std::endl;
    }
    // end::code[]
}

// vim:et
