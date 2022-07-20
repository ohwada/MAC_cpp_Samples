/**
 * hello_world.cc
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/libsigcplusplus/libsigcplusplus/tree/master/examples
 
/* Copyright 2003 - 2016, The libsigc++ Development Team
 *
 *  Assigned to the public domain.  Use as you wish without
 *  restriction.
 */

#include <iostream>
#include <string>

#include <sigc++/sigc++.h>


/**
 * on_print
 */
void on_print(const std::string& str)
{
  std::cout << str;
}


/**
 * main
 */
int main()
{
  sigc::signal<void(const std::string&)> signal_print;

  signal_print.connect(sigc::ptr_fun(&on_print));

  signal_print.emit("hello world\n");

  return 0;
}

