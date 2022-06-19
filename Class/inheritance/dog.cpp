/**
 * dog.cpp
 * 2022-06-01 K.OHWADA
 */

// Dog class: inheritance of Animal class 

#include "dog.h"

/**
 * constractor
 */


  Dog::Dog(std::string name, int age) : Animal(name, age) 
{
    // none
}


/**
 * destractor
 */
  Dog::~Dog()
{
 	// none
}


 /**
 * bark
   * @return {string}
 */
  std::string Dog::bark()
{
    return std::string( "waoon");
  }