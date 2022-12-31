/**
 *  http_file_server_async.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include "async_server.hpp"
#include "request_parser.hpp"
#include "response_builder.hpp"


/**
 *  do_handle_read
 */
   std::string do_handle_read(std::string doc_root, std::string read_data)
{

    const std::string SLASH("/");

    std::cout << "doc_root: " << doc_root << std::endl;

  std::cout << std::endl;
    std::cout << "request" << std::endl;
    std::cout << read_data << std::endl;

    auto path = parse_path(read_data);

   std::cout << "path: " << path << std::endl;

    std::string fname;
    if(path == SLASH){
        fname = "index.html";
    } else {
        fname = path;
    }

    auto fpath = make_path(doc_root, fname);

    std::cout << "fpath: " << fpath << std::endl;

   std::string response;

    if(existsFile(fpath)){
        response = build_response_file(fpath);
    } else {
        response = build_response_not_found(path);
    }

  std::cout << std::endl;
    std::cout << "response size: " <<  response.size() << std::endl;

    return response;
}


/**
 *  main
 */
int main(int argc, char* argv[])
{

    unsigned short port = 8080;

    std::string doc_root("www");

    if (argc == 2){
        port = std::atoi(argv[1]);
    } else {
      std::cerr << "Usage: http_server <port>\n";
    }

    run_server(port, doc_root);
 
  return 0;
}
