// File: main.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/chapter-custom-signals-example.html

#include "server.h"
#include "client.h"
#include <iostream>

int main(int, char**)
{
  Server server;
  Client client;

  //Connect a Server signal to the signal handler in Client.
  server.signal_something().connect(sigc::mem_fun(client,
              &Client::on_server_something) );

  std::cout << "Before Server::do_something()" << std::endl;

  //Tell the server to do something that will eventually cause it to emit the
  //"something" signal.
  server.do_something();    // Client::on_server_something() will run before
                            // Server::do_something() has completed.

  std::cout << "After Server::do_something()" << std::endl;

  return 0;
}