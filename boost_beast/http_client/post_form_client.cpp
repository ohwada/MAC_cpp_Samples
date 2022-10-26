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


using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    string host("postman-echo.com");
    int port = 80;
    string target("/post");

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
    


    string postdata(  
    "project=curl_file&name=michael&age=30" );

    auto req = build_http_post_request(host, target, postdata, CONTENT_TYPE_FORM );

    cout << endl;
    cout << "request" << endl;
    cout << req << endl;

string response;
string error;

bool ret = http_client(host, port, req, response, error);
if(!ret){
    cerr << "http_client faild: " << error << endl;
    return EXIT_FAILURE;
}

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    return EXIT_SUCCESS;
}


