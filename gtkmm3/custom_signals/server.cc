// File: server.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/chapter-custom-signals-example.html'

#include "server.h"
#include <iostream>

Server::Server()
{
}

Server::~Server()
{
}

Server::type_signal_something Server::signal_something()
{
  return m_signal_something;
}

void Server::do_something()
{
  m_signal_something.emit(false, 5);
}