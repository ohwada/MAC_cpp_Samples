/**
 * modify_remove.cpp
 * 2022-06-01 K.OHWADA
 */

// This is an example of removing attributes/nodes from the document
// original : https://pugixml.org/docs/quickstart.html

// g++ modify_remove.cpp `pkg-config --cflags --libs  pugixml` -o remove

#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
    pugi::xml_document doc;
    if (!doc.load_string("<node><description>Simple node</description><param name='id' value='123'/></node>")) return -1;

    // tag::code[]
    // remove description node with the whole subtree
    pugi::xml_node node = doc.child("node");
    node.remove_child("description");

    // remove id attribute
    pugi::xml_node param = node.child("param");
    param.remove_attribute("value");

    // we can also remove nodes/attributes by handles
    pugi::xml_attribute id = param.attribute("name");
    param.remove_attribute(id);
    // end::code[]

    doc.print(std::cout);
    return 0;
}


