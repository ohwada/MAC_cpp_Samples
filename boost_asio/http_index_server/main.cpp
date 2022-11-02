/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// simple http server
// return fixed response index.html

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/http/server/main.cpp


#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "server.hpp"
#include "request_handler.hpp"


/**
 * on_request
 */
void on_request(const http::server::request& req, http::server::reply& rep, std::string request_path)
{
    std::string full_path("www/index.html");
    do_response_file(rep, full_path);
}


/**
 * run_server
 */
bool run_server(std::string port)
{
   std::string address("127.0.0.1");
    std::string doc_root("www");

  try
  {
    // Initialise the server.
    http::server::server s(address, port, doc_root);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
    return false;
  }

    return true;
}

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string port("8080");

    if(argc == 2) {
      	port = argv[1];
    } else {
        cout << "Usage: " << argv[0] << "  <port> " << endl;
    }

    cout << "port: " << port << endl;

    run_server(port);

  return 0;
}
