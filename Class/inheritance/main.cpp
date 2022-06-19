/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include "dog.h"
#include "cat.h"

using namespace std;

// prototype
void printAnimal(string cls, string name, int age, string bark);


/**
 * main
 */
int main()
{

	Animal a( string("milk"), 1);
	printAnimal( "Animal", a.getName(), a.getAge(), a.bark() );

	Dog d( string("taro"), 2);
	printAnimal( "Dog",  d.getName(), d.getAge(), d.bark() );

	Cat c( string("tama"), 3);
	printAnimal( "Cat",  c.getName(), c.getAge(), c.bark() );

return 0;
}


/**
 * printAnimal
 */
void printAnimal( string cls, string name, int age, string bark )
{
	cout << cls << ": "<< name << ": "<< age<< ": "<< bark << endl;
}

// Animal: milk: 1: moo
// Dog: taro: 2: waoon
// Cat: tama: 3: nya
