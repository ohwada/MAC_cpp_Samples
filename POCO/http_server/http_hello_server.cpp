/**
 *  http_hello_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPTimeServer/src/HTTPTimeServer.cpp

#include <iostream>
#include "poco_http_server.hpp"



/**
 * on_request
 */
void on_request(HTTPServerRequest& request, HTTPServerResponse& response)
{

	std::string TEXT("Hello World");

	Application& app = Application::instance();
	app.logger().information("Request from " + request.clientAddress().toString());

	response.setContentType("text/plain");

	std::ostream& ostr = response.send();
	ostr << TEXT;
}


/**
 *  main
 */
int main(int argc, char** argv)
{
    unsigned short port = 9980;

	MyServer app;
    app.setPort(port);

	return app.run(argc, argv);
}
