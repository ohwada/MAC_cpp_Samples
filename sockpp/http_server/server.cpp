/**
 * server.cpp
 * 2022-06-01 K.OHWADA
 */

// A multi-threaded TCP echo server for sockpp library.
// This is a simple thread-per-connection TCP server.
// original : https://github.com/fpagliughi/sockpp/blob/master/examples/tcp/tcpechosvr.cpp

#include <iostream>
#include <thread>
#include "sockpp/tcp_acceptor.h"
#include "sockpp/version.h"
#include "http_server.hpp"

using namespace std;


// The main thread runs the TCP port acceptor. Each time a connection is
// made, a new thread is spawned to handle it, leaving this main thread to
// immediately wait for the next connection.

bool server(int port, std::string response)
{
	sockpp::socket_initializer sockInit;

	sockpp::tcp_acceptor acc(port);

	if (!acc) {
		std::cerr << "Error creating the acceptor: " << acc.last_error_str() << std::endl;
		return false;
	}


	std::cout << "listen port " << port << std::endl;

	while (true) {
		sockpp::inet_address peer;

		// Accept a new client connection
		sockpp::tcp_socket sock = acc.accept(&peer);
		std::cout << "Received a connection request from " << peer << std::endl;

		if (!sock) {
			std::cerr << "Error accepting incoming connection: " 
				<< acc.last_error_str() << std::endl;
		}

const size_t BUFSIZE = 1024;
	char buf[BUFSIZE];

	ssize_t size = sock.read(buf, BUFSIZE);
	if( size > 0) {
		std::cout << std::endl;
		std::cout << "request" << std::endl;
		std::cout << buf << std::endl;
		sock.write_n(response.c_str(), response.size() );
	}

	} // while

	return true;
}


/**
 * main
 */
int main(int argc, char* argv[])
{
	    in_port_t port = 12345;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        cout << "Usage: " << argv[0] << " [port] " << endl;
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

	server(port, response);

	return 0;
}

// listen port 12345
