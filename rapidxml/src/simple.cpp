/**
 * simple.cpp
 * 2022-06-01 K.OHWADA
 */

// simple parser
// original : https://codezine.jp/article/detail/10235

// g++ simple.cpp -std=c++11 -o simple


#include "rapidxml.hpp"

#include <iostream>
#include <string>

using namespace std;

// abbreviated rapidxml as rx
namespace rx = rapidxml;


/**
 * main
 */
int main() 
{
  string xml = R"(<function include="&lt;cstdio&gt;"><return type="int"/>printf</function>)";

  rx::xml_document<> doc;
  doc.parse<0>(&xml[0]);

// the <function> node directly under the root and its attributes 
  rx::xml_node<>* node = doc.first_node("function");
  rx::xml_attribute<>* attr = node->first_attribute();

  cout << "node : " << node->name() << "=[" << node->value() << "]\n";
  cout << "attr : " << attr->name() << "=[" << attr->value() << "]\n";
  cout << endl;

// replace'\0' with '#'
  for (char ch : xml) { cout << (ch != '\0' ? ch : '#'); }
  cout << endl;
    return 0;
}

// node : function=[printf]
// attr : include=[<cstdio>]

