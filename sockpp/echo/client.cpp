/**
 * client.cpp
 * 2022-06-01 K.OHWADA
 */

// Simple TCP echo client
// original : https://github.com/fpagliughi/sockpp/blob/master/examples/tcp/tcpecho.cpp


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
 #include <boost/format.hpp>
#include "sockpp/tcp_connector.h"
#include "sockpp/version.h"
#include "port.h"

using namespace std;
using namespace std::chrono;



bool client(std::string host, unsigned short port)
{

  const int MAX_LOOP = 100;

    const long SLEEP = 1000; // 1 sec

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

	cout << "Created a connection from " << conn.address() << endl;

    // Set a timeout for the responses
    if (!conn.read_timeout(seconds(5))) {
        cerr << "Error setting timeout on TCP stream: "
                << conn.last_error_str() << endl;
    }

	std::string str, sret;

	for(int i=0; i<MAX_LOOP; i++) 
{
    str = boost::str( boost::format("%03d") % i ) ;
		if (conn.write(str) != ssize_t(str.length())) {
			std::cerr << "Error writing to the TCP stream: "
				<< conn.last_error_str() << std::endl;
			break;
		}

        auto length = str.length();
		sret.resize(length);
		ssize_t n = conn.read_n(&sret[0], length);
		if (n != ssize_t(length)) {
			std::cerr << "Error reading from TCP stream: "
				<< conn.last_error_str() << std::endl;
			// break;
		}

		std::cout << "rcv: " << sret << std::endl;

std::this_thread::sleep_for(std::chrono:: milliseconds (SLEEP));

	} // for

	return true;
}


/**
 * main
 */
int main(int argc, char* argv[])
{
	 cout << "Sample TCP echo client for 'sockpp' "
		 << sockpp::SOCKPP_VERSION << '\n' << endl;

	string host = (argc > 1) ? argv[1] : "localhost";
	in_port_t port = (argc > 2) ? atoi(argv[2]) : PORT;

    cout << host << endl;
    cout << "port: " <<port << endl;

    client(host, port);

    return 0;
}

