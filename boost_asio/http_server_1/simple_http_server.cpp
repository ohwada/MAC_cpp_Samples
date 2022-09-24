/**
 * simple_http_server.cpp
 * 2022-06-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response


#include <iostream>
#include <string>
#include "http_server.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    int port = 8080;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        cerr << "Usage: " << argv[0] << " [port] " << endl;
    }

    cout << "port: " << port << endl;

// build response
    string html;
    bool ret1 = get_index_html(html);
    if(!ret1){
        cerr << "cannot get_index_html" << endl;
        return EXIT_FAILURE;
    }

    string response = build_response(html);

    cout << "response" << endl;
    cout << response << endl;

    http_server(port, response);

return EXIT_SUCCESS;

}

 
// listen port: 8080

