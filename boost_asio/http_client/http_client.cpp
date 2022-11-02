/**
 * http_client.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/http/client/sync_client.cpp

#include <iostream>
#include <string>
#include "http_client.hpp"
#include "request_builder.hpp"
#include "save.hpp"

using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    std::string host("example.com");
    std::string path("/");


    if(argc == 3) {
      	host = argv[1];
      	path = argv[2];
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [host] [path] " << endl;
    }

    cout << "host: " << host << endl;
    cout << "path: " << path << endl;

    std::string request = build_http_request(host, path);

    cout << endl;
    cout << "request" << endl;
    cout << request << endl;
  
    string body;
    bool is_verbose= true;

  http_client(host, request, body, is_verbose);

    cout << endl;
    cout << "body size: " << body.size() << endl;

    bool is_save_verbose= true;
    save_body(body, is_save_verbose);

  return 0;
}
