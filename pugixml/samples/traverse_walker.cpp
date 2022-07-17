/**
 * traverse_walker.cpp
 * 2022-06-01 K.OHWADA
 */

// This is an example of traversing tree hierarchy with xml_tree_walker
// original : https://pugixml.org/docs/quickstart.html

// g++ traverse_walker.cpp `pkg-config --cflags --libs  pugixml` -o walker


#include "pugixml.hpp"

#include <iostream>


const char* node_types[] =
{
    "null", "document", "element", "pcdata", "cdata", "comment", "pi", "declaration"
};


/**
 * struct simple_walker
 */
// tag::impl[]
struct simple_walker: pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node)
    {
        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

        std::cout << node_types[node.type()] << ": name='" << node.name() << "', value='" << node.value() << "'\n";

        return true; // continue traversal
    }
};
// end::impl[]


/**
 * main
 */
int main()
{
    pugi::xml_document doc;
    if (!doc.load_file("tree.xml")) return -1;

    // tag::traverse[]
    simple_walker walker;
    doc.traverse(walker);
    // end::traverse[]
    return 0;
}
