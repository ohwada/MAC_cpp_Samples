/**
 * http_index_server.cpp
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
void on_request(const http::server::request& req, http::server::reply& rep, std::string doc_root, std::string request_path)
{
  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/')
  {
    request_path += "index.html";
  }


 // Open the file to send back.
  std::string full_path = doc_root + request_path;

    std::cout <<  "file: " << full_path << std::endl;

    do_response_file(rep, full_path);
}


/**
 * run_server
 */
bool run_server(std::string port, std::string doc_root)
{
   std::string address("127.0.0.1");

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
    std::string doc_root("www2");

    if(argc == 2) {
      	port = argv[1];
    } else {
        cout << "Usage: " << argv[0] << "  <port> " << endl;
    }

    cout << "port: " << port << endl;

    run_server(port, doc_root);

  return 0;
}
