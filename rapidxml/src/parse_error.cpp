/**
 *  parse_error.cpp
 * 2022-06-01 K.OHWADA
 */

// handling parse error
// original : https://codezine.jp/article/detail/10235

// g++ parse_error.cpp  -std=c++11 -o error

#include "rapidxml.hpp"

#include <iostream>
#include <string>

using namespace std;
namespace rx = rapidxml;


/**
 *  main
 */
int main() 
{
  //                               ↓there is no "..." here!
  string xml = R"(<function include=><return type="int"/>printf</function>)";
  rx::xml_document<char> doc;
  try {
    doc.parse<0>(&xml[0]);
  } catch (const rx::parse_error& ex) {
    cerr << ex.what() << " @ [" << ex.where<char>() << "]＼n";
  }
    return 0;
}
