/**
 * MiniWebServer.cpp
 * 2022-06-01 K.OHWADA
 */

// reference :https://codezine.jp/article/detail/1792

#include <iostream>
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/File.h"
#include "parse_filename.hpp"

const int PORT  = 9980;
const std::string ROOT("www"); 


/**
 * get_mime
 */
std::string get_mime( std::string fpass )
{
	std::string ext = getFileNameExt(fpass);
	std::string mime;
	if(ext == "html"){
 		mime = "text/html";
	}else if(ext == "png"){
 		mime = "image/png";
	}
	return mime;
}


/**
 * get_fpass
 */
std::string get_fpass( std::string uri)
{
	if( uri == "/" ) {
		uri = "/index.html";
	}
	std::string fpass = ROOT + uri;
	return fpass;
}


/**
 * class NotFileHandle
 */
class NotFileHandler: public Poco::Net::HTTPRequestHandler
{
public:
	
	void handleRequest(Poco::Net::HTTPServerRequest& request,
						Poco::Net::HTTPServerResponse& response)
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		response.setContentType("text/html");

		std::ostream& ostr = response.send();
		ostr << "<html><head>";
		ostr << "<title>MiniWebServer powered by POCO</title>";
		ostr << "</head><body>Not Found File<br />";
		ostr << "</body></html>";
	}
};


/**
 * class FileRequestHandler
 */
class FileRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	
	void handleRequest(Poco::Net::HTTPServerRequest& request,
							Poco::Net::HTTPServerResponse& response)
	{
		try{
// std::cout << "uri: " << request.getURI() << std::endl;
std::string fpass = get_fpass( request.getURI() );
std::string mime = get_mime( fpass );
			response.sendFile(fpass, mime);
		}
		catch(Poco::Exception& )
		{
		}
	}
};


/**
 * class MiniRequestHandlerFactory
 */
class MiniRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:

	Poco::Net::HTTPRequestHandler*
		createRequestHandler(const Poco::Net::HTTPServerRequest& request)
	{
std::cout << "uri: " << request.getURI() << std::endl;
std::string fpass = get_fpass( request.getURI() );

		Poco::File f(fpass);
		if ( !f.exists() || !f.isFile() ) return new NotFileHandler();

		return new FileRequestHandler();
	}
};


/**
 * class MiniWebServer:
 */
class MiniWebServer: public Poco::Util::ServerApplication
{

protected:
	
	int main(const std::vector<std::string>& args)
	{

// Maximum number of simultaneous client connections
		int maxThreads = 1; 

// Setting the number of connected threads
		Poco::ThreadPool::defaultPool().addCapacity(maxThreads);

// Set value class
		Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
		

// Maximum number of connection request sockets
		pParams->setMaxQueued(100);
		pParams->setMaxThreads(maxThreads);
		Poco::Net::ServerSocket svs(PORT);	
	
std::cout << "listen: "<< PORT << std::endl;

// Instance of HTTP server class
		Poco::Net::HTTPServer	srv(new MiniRequestHandlerFactory(), svs, pParams); 

// start Server 
		srv.start(); 

// Wait until CTRL-C is pressed
// Or until the process is killed
		waitForTerminationRequest();

// stop Server
		srv.stop();

		return Application::EXIT_OK;
	}
};


/**
 * main
 */
int main(int argc, char* argv[])
{
	MiniWebServer app;
	return app.run(argc, argv);
}

