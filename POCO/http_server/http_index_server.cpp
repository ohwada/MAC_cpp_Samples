/**
 *  http_index_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPTimeServer/src/HTTPTimeServer.cpp


#include "poco_http_server.hpp"


/**
 *  on_request
 */
void on_request(HTTPServerRequest& request, HTTPServerResponse& response)
{

	Application& app = Application::instance();
	app.logger().information("Request from " + request.clientAddress().toString());

    std::string fpath("data/index.html");
    std::string mime("text/html");

	try{
		response.sendFile(fpath, mime);
	}
	catch(Poco::Exception e )
	{
		std::cerr << e.what() << std::endl;
	}

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
