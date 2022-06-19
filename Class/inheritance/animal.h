#pragma once
/**
 * animal.h
 * 2022-06-01 K.OHWADA
 */

// Animal class: base class
// one virtual method

#include <string>

/**
 * class Animal
 */
class Animal {
public:
  Animal(std::string name, int age);
  ~Animal();
  std::string  getName();
  int getAge();
  virtual std::string  bark();

private:
   std::string _name;
    int _age;
};

