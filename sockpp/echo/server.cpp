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
#include "port.h"

using namespace std;


// The thread function. This is run in a separate thread for each socket.
// Ownership of the socket object is transferred to the thread, so when this
// function exits, the socket is automatically closed.

void run_echo(sockpp::tcp_socket sock)
{
	ssize_t n;
	char buf[512];

	while ((n = sock.read(buf, sizeof(buf))) > 0)
{
		std::cout << "rcv: " << buf << std::endl;
	// echo back
		sock.write_n(buf, n);

} //while

	std::cout << "Connection closed from " << sock.peer_address() << std::endl;
}


// The main thread runs the TCP port acceptor. Each time a connection is
// made, a new thread is spawned to handle it, leaving this main thread to
// immediately wait for the next connection.

bool server(int port)
{
	sockpp::socket_initializer sockInit;

	sockpp::tcp_acceptor acc(port);

	if (!acc) {
		std::cerr << "Error creating the acceptor: " << acc.last_error_str() << std::endl;
		return false;
	}

    //cout << "Acceptor bound to address: " << acc.address() << endl;

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
		else {
			// Create a thread and transfer the new stream to it.
			thread thr(run_echo, std::move(sock));
			thr.detach();
		}
	} // while

	return true;
}


/**
 * main
 */
int main(int argc, char* argv[])
{
	
	 cout << "Sample TCP echo server for 'sockpp' "
	 	<< sockpp::SOCKPP_VERSION << '\n' << endl;

	server(PORT);

	return 0;
}

// Sample TCP echo server for 'sockpp' v0.7.1
// listen port 12345
