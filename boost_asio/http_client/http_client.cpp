/**
 * http_client.cpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Client
// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T


#include <iostream>
#include <boost/asio.hpp>
#include "asio_socket.hpp"
#include "resolver.hpp"
#include "http_client.hpp"
#include "file_util.hpp"
#include "response_parser.hpp"
#include "save.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    std::string host("example.com");

    int port = PORT_HTTP;

    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [host] [port] " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;

    string request =
    build_http_root_path_request( host);


    cout << endl;
    cout << "request" << endl;
    cout << request << endl;

    string response;

    bool ret1 = http_client(host, port, request, response);
    if(!ret1){
        return EXIT_FAILURE;
    }

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    bool is_save_verbose = true;
    save_reponse( response,  is_save_verbose );

    string header;
    string body;

    bool ret2 = split_header_body(response, header, body);
   if(!ret2){
        return EXIT_FAILURE;
    }

    cout << endl;
    cout << "header" << endl;
    cout << header << endl;

    bool is_chunked = is_transfer_encoding_chunked(header);

    cout  << std::boolalpha << "is_chunked: " << is_chunked << endl;

    cout << "body size: " <<  body.size() << endl;


    string chunk_size;
    string slim_body;

    if( is_chunked ) {
        bool ret3 = parse_chunked_body(body,  chunk_size, slim_body);

        cout << endl;
        cout << "chunk size: " << chunk_size << endl;

        cout << "slim body size: " <<  slim_body.size() << endl;
    // cout << slim_body << endl;

        if(ret3){
            save_body( slim_body, is_save_verbose);
        } else {
            save_body( body, is_save_verbose);
        }

    } else {
            save_body( body, is_save_verbose);
    }


    return EXIT_SUCCESS;
}

// connect: example.com : 80
// HTTP/1.1 200 OK
//  <title> Example Domain </title>

