/**
 * http_file_server.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPFormServer/src/HTTPFormServer.cpp'
// reference :https://codezine.jp/article/detail/1792

#include <iostream>
#include "poco_file_server.hpp"


/**
 *  on_request
 */
void on_request(HTTPServerRequest& request, HTTPServerResponse& response, std::string root)
{
    log_client(request);

    std::string uri = request.getURI();
	Poco::File file = get_file( root, uri );

	std::cout<< uri << std::endl;
	std::cout<< file.path() << std::endl;

		if ( file.exists() && file.isFile() ) {
            send_file(response, file);
		} else {
	        send_notfound(response, uri);
        }

}


/**
 * main
 */
int main(int argc, char* argv[])
{

    unsigned short port = 9983;
	std::string root("www");

	FileServer app;
    app.setPort(port);
    app.setRoot(root);

	return app.run(argc, argv);
}

