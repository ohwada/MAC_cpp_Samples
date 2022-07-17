/**
 * modify_add.cpp
 * 2022-06-01 K.OHWADA
 */

// This is an example of adding new attributes/nodes to the document
// original : https://pugixml.org/docs/quickstart.html

// g++  modify_add.cpp `pkg-config --cflags --libs  pugixml` -o add

#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
    pugi::xml_document doc;

    // tag::code[]
    // add node with some name
    pugi::xml_node node = doc.append_child("node");

    // add description node with text child
    pugi::xml_node descr = node.append_child("description");
    descr.append_child(pugi::node_pcdata).set_value("Simple node");

    // add param node before the description
    pugi::xml_node param = node.insert_child_before("param", descr);

    // add attributes to param node
    param.append_attribute("name") = "version";
    param.append_attribute("value") = 1.1;
    param.insert_attribute_after("type", param.attribute("name")) = "float";
    // end::code[]

    doc.print(std::cout);
    return 0;
}

