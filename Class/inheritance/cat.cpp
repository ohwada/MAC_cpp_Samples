/**
 * cat.cpp
 * 2022-06-01 K.OHWADA
 */

// Cat class: inheritance of Animal class

#include "cat.h"


/**
 * constractor
 */
 Cat::Cat(std::string name, int age) : Animal(name, age) 
{
    // none
}


/**
 * destractor
 */
 Cat::~Cat()
{
 	// none
}


/**
 * bark
   * @return {string}
 */
 std::string Cat::bark()
{
    return std::string( "nya");
 }
