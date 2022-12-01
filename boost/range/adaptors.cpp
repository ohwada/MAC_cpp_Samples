// adaptors.cpp
// Boost.Range.Adaptors
// https://qiita.com/rinse_/items/f00bb2a78d14c3c2f9fa

#include <iostream>
#include <vector>
#include <boost/range/irange.hpp>
#include <boost/range/adaptor/strided.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/reversed.hpp>

int main()
{
// make a string
  std::string str;
  boost::copy(
/* create a range of elements from 'a' to 'z' */
    boost::irange<char>('a', 'z'+1)
/* capitalize all elements */
      | boost::adaptors::transformed([](char c) { return c - ('a' - 'A'); }) 
/* reverse order */
      | boost::adaptors::reversed, 
/* append to string */
    std::back_inserter(str));

// output: ZYXW...A
  std::cout << str << std::endl; 


// create a suitable number sequence.
  boost::copy(
/* create a range of elements from 0 to 99 */
    boost::irange(0, 100)
/* skip one element */
      | boost::adaptors::strided(2)
/* doubles all elements */
      | boost::adaptors::transformed([](int n) { return n*2; }), 
/* output with spaces */
    std::ostream_iterator<int>(std::cout, " "));
  // output: 0, 4, 8, 12, ..., 196
std::cout << std::endl;

    return 0;
}

// ZYXWVUTSRQPONMLKJIHGFEDCBA
// 0 4 8 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76 80 84 88 92 96 100 104 108 112 116 120 124 128 132 136 140 144 148 152 156 160 164 168 172 176 180 184 188 192 196

