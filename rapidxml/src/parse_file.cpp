/**
 *  parse_file.cpp
 * 2022-06-01 K.OHWADA
 */

// parse XML file
// original : https://codezine.jp/article/detail/10235

// g++ parse_file.cpp -o parse

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp" // rapidxml::file

#include <iostream>

using namespace std;
namespace rx = rapidxml;

int main() {
  rx::xml_document<> doc;
  rx::file<> input("trial.xml");
  doc.parse<0>(input.data());

  rx::xml_node<>* node = doc.first_node("person");
  for ( rx::xml_node<>* child = node->first_node(); child != nullptr; child = child->next_sibling() ) {
    cout << child->name() << " : [" << child->value() << "]\n";
  }
    return 0;
}

