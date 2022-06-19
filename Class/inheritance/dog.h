#pragma once
/**
 * dog.h
 * 2022-06-01 K.OHWADA
 */

// Dog class: inheritance of Animal class
// one  override method

#include "animal.h"

class Dog : public Animal 
{
	public:
		Dog(std::string name, int age);
		~Dog();
		std::string bark() override;
  };