// File: client.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/chapter-custom-signals-example.html'

#include "client.h"
#include <iostream>

Client::Client()
{
}

Client::~Client()
{
}

void Client::on_server_something(bool a, int b)
{
  std::cout << "Client::on_server_something() called with these parameters: "
      << a << ", " << b << std::endl;
}