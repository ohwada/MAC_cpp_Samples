/**
 * tclap sample
 * 2020-03-01 K.OHWADA
 */

// command line parser
// reference :  http://tclap.sourceforge.net/manual.html#EXAMPLE

#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>


/**
 * main
 */
int main(int argc, char** argv)
{

	// Wrap everything in a try block.  Do this every time, 
	// because exceptions will be thrown for problems.
	try {  

	// Define the command line object, and insert a message
	// that describes the program. The "Command description message" 
	// is printed last in the help text. The second argument is the 
	// delimiter (usually space) and the last one is the version number. 
	// The CmdLine object parses the argv array based on the Arg objects
	// that it contains. 
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");

	// Define a value argument and add it to the command line.
	// A value arg defines a flag and a type of value that it expects,
	// such as "-n Bishop".
	TCLAP::ValueArg<std::string> nameArg("n","name","Name to print",true,"homer","string");

	// Add the argument nameArg to the CmdLine object. The CmdLine object
	// uses this Arg to parse the command line.
	cmd.add( nameArg );

	// Define a switch and add it to the command line.
	// A switch arg is a boolean argument and only defines a flag that
	// indicates true or false.  In this example the SwitchArg adds itself
	// to the CmdLine object as part of the constructor.  This eliminates
	// the need to call the cmd.add() method.  All args have support in
	// their constructors to add themselves directly to the CmdLine object.
	// It doesn't matter which idiom you choose, they accomplish the same thing.
	TCLAP::SwitchArg reverseSwitch("r","reverse","Print name backwards", cmd, false);

	// Parse the argv array.
	cmd.parse( argc, argv );

	// Get the value parsed by each arg. 
	std::string name = nameArg.getValue();
	bool reverseName = reverseSwitch.getValue();

	// Do what you intend. 
	if ( reverseName )
	{
		std::reverse(name.begin(),name.end());
		std::cout << "My name (spelled backwards) is: " << name << std::endl;
	}
	else
		std::cout << "My name is: " << name << std::endl;


	} catch (TCLAP::ArgException &e)  // catch any exceptions
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }

	return 0;
}

