/**
 * client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include "tcp_client.hpp"
#include "request_builder.hpp"
#include "save.hpp"
#include "response_parser.hpp"

// global
std::string request;
std::string response;


/**
 *  on_connect
 */
void on_connect( Poco::Net::StreamSocket *ss)
{
    tcp_send(*ss, request);

    size_t block_size = 1024;

// www.google.com needs 65 times
// response size is 56680
    int loop = 100;

    bool is_verbose = true;

    response = tcp_block_read(*ss, block_size, loop, is_verbose);        
}

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    string host("example.com");

    Poco::UInt16 port = PORT_HTTP;

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

    string path = ROOT_PATH;

    request = build_http_request(host, path);

    cout << endl;
    cout << "request" << endl;
    cout << request << endl;

    run_client(host,  port); 
   
    cout << endl;
    cout << "response" << endl;
    //cout << response << endl;
    cout << "response size: " << response.size() << endl;

    bool is_save_verbose = true;

    save_response(response, is_save_verbose);

    string header;
    string body;

    split_header_body(response, header, body);

    cout << endl;
    cout << "header" << endl;
    cout << header << endl;

    cout << endl;
    cout << "body" << endl;
   // cout << body << endl;
    cout << "body size: " << body.size() << endl;

    save_body(body, is_save_verbose);

    return 0;
}


