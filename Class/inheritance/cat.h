#pragma once
/**
 * cat.h
 * 2022-06-01 K.OHWADA
 */

// Cat class: inheritance of Animal class
// one  override method

#include "animal.h"

class Cat : public Animal 
{
public:
	Cat(std::string name, int age);
	~Cat();
	std::string bark() override;

};