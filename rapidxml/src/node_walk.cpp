/**
 *  node_walk.cpp
 * 2022-06-01 K.OHWADA
 */

// traverse between nodes
// original : https://codezine.jp/article/detail/10235

// g++  node_walk.cpp -o walk

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>

using namespace std;
namespace rx = rapidxml;


/**
 *  walk
 * recursively enumerate nodes with name
 */
void walk(rx::xml_node<>* node, const char* name) {
  for (rx::xml_node<>* child = node->first_node(name); child != nullptr; child = child->next_sibling(name)) {
    cout << child->name() << " : [" << child->value() << "]\n";
    walk(child, name);
  }
}


/**
 *  main
 */
int main() {
  rx::xml_document<> doc;
  rx::file<> input("trial.xml");
  doc.parse<rx::parse_trim_whitespace>(input.data());
  walk(&doc, "person"); // xml_document は xml_node の派生クラス
    return 0;
}

