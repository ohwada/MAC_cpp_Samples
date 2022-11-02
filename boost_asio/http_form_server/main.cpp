/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// http form server
// return parsed query string 

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/http/server/main.cpp


// TODO:  
// POST method  

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "server.hpp"
#include "request_handler.hpp"
#include "form.hpp"


/**
 * on_request
 */
void on_request(const http::server::request& req, http::server::reply& rep, std::string request_path)
{

   // std::cout << "metod: " << req.method << std::endl;
   // std::cout << "request_path: " << request_path << std::endl;

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/')
  {
        std::string full_path("www/index_get.html");
        do_response_file(rep, full_path);
        return;
    }


    std::string key;
    std::string value;
    parse_request_path(request_path, key, value);

    // std::cout << "key: " << key << std::endl;
    // std::cout << "value: " << value << std::endl;

    std::string method(req.method);

    std::string text = build_msg_form(method, key, value);

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << text << std::endl;

    std::string mime("text/html");

    do_response_text(rep, text, mime);
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
