/**
 * http_client.cpp
 * 2020-07-01 K.OHWADA
 */

// HTTP Client, synchronous
// original : https://github.com/boostorg/beast/blob/develop/example/http/client/sync/http_client_sync.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include "http_client.hpp"
#include "file_util.hpp"


/**
 * save_body
 */
bool save_body( std::string body )
{
  

    std::string dir("log");
    std::string prefix("body");
    std::string ext("html");

    std::string filename;

    getTimestampFileName(prefix, ext, filename);

    std::string path = make_path(dir, filename);

    return  writeTextFile( path, body);
}


using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    string host("www.example.com");
    int port = 80;
    string target("/");

    if(argc == 4) {
        host = argv[1];
        port = atoi(argv[2]);
        target = argv[3];
    } else if(argc == 3) {
        host = argv[1];
        port = atoi(argv[2]);
    } else if(argc == 2) {
        host = argv[1];
    } else {
        std::cout <<
            "Usage: " << argv[0] <<" [host] [port] [target] \n" << endl;
    }
 

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;
    cout << "target: " << target << endl;
    
    auto req = build_http_get_request(host, target );

    cout << endl;
    cout << "request" << endl;
    cout << req << endl;

    string response;
    string error;

    bool ret1 = http_client(host, port, req, response, error);
    if(!ret1){
        cerr << "http_client faild: " << error << endl;
        return EXIT_FAILURE;
    }

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    string header;
    string body;

    bool ret2 = split_header_body(response, header, body);
    if(!ret2){
        return EXIT_FAILURE;
    }

     cout << endl;
    cout << "header" << endl;
    cout <<  header << endl;

     cout << endl;
    cout << "body" << endl;
    cout <<  body << endl;

    bool ret3 = save_body(body);
    if(!ret3){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// connect: www.example.com : 80
// HTTP/1.1 200 OK
// <title>Example Domain</title>

