/**
 * client.cpp
 * 2022-06-01 K.OHWADA
 */

// Simple TCP echo client
// original : https://github.com/fpagliughi/sockpp/blob/master/examples/tcp/tcpecho.cpp


#include <iostream>
#include <string>
#include <chrono>
#include <boost/format.hpp>
#include "sockpp/tcp_connector.h"
#include "http_client.hpp"


using namespace std;
using namespace std::chrono;


bool client(std::string host, in_port_t port, std::string request, std::string &response)
{
    const long TIMEOUT = 60; // sec

	sockpp::socket_initializer sockInit;

// Implicitly creates an inet_address from {host,port}
// and then tries the connection.
	sockpp::tcp_connector conn({host, port});
	if (!conn) {
		std::cerr << "Error connecting to server at "
			<< sockpp::inet_address(host, port)
			<< "\n\t" << conn.last_error_str() << std::endl;
		return false;
	}

	// cout << "Created a connection from " << conn.address() << endl;

    ssize_t size = conn.write(request);

		if ( size != ssize_t(request.length())) {
			std::cerr << "Error writing to the TCP stream: "
				<< conn.last_error_str() << std::endl;
		}

    // Set a timeout for the responses
    if (!conn.read_timeout(seconds( TIMEOUT))) {
        cerr << "Error setting timeout on TCP stream: "
                << conn.last_error_str() << endl;
    }

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];

	conn.read_n(buf, BUFSIZE);

    response = buf;

	return true;
}


/**
 * main
 */
int main(int argc, char* argv[])
{

   string host("example.com");

    in_port_t port = (in_port_t)PORT_HTTP;

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
    client(host, port, request, response);

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    return 0;
}

