/**
 * animal.cpp
 * 2022-06-01 K.OHWADA
 */

// Animal class: base class

#include "animal.h"

/**
 * constractor
 */
  Animal::Animal(std::string name, int age)
{
	_name = name;
	_age = age;
}


/**
 * destractor
 */
  Animal::~Animal()
{
    // none
}


  /**
   * getName
   * @return {string}
   */
  std::string  Animal::getName()
{
    return _name;
  }


  /**
   * getAge
   * @return {int}
   */
  int Animal::getAge()
{
    return _age;
  }


  /**
   * bark
   * @return {string}
   */
 std::string  Animal::bark()
{
    return std::string("moo");
}


