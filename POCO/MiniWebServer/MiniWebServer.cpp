/**
 * MiniWebServer.cpp
 * 2022-06-01 K.OHWADA
 */

// reference :https://codezine.jp/article/detail/1792?p=4

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

const int PORT  = 9980;

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
			std::string fpass = ".";
			fpass += request.getURI();

			response.sendFile(fpass, "text/html");
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
		std::string fpass = ".";
		fpass += request.getURI();

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

