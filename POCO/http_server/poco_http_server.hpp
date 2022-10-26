#pragma once
/**
 *  htttp_server.hpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/MyServer/src/MyServer.cpp


#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include <iostream>


using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;


// prototype
void on_request(HTTPServerRequest& request, HTTPServerResponse& response);


/**
 *  class MyRequestHandler
 */
class MyRequestHandler: public HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
	MyRequestHandler()
	{
		// none
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		on_request(request, response);
	}

private:
};


/**
 *  class MyRequestHandlerFactory
 */
class MyRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
	MyRequestHandlerFactory()
	{
		// none
	}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		const std::string SLASH("/");
		if (request.getURI() == SLASH)
			return new MyRequestHandler();
		else
			return 0;
	}

private:
};


/**
 *  class MyServer
 */
// https://docs.pocoproject.org/current/Poco.Util.ServerApplication.html
class MyServer: public Poco::Util::ServerApplication
	/// The main application class.

	/// Youcan specify the port on which the server is listening (default
	/// 9980) and the format of the date/time string sent back to the client.
	///
	/// To test the TimeServer you can use any web browser (http://localhost:9980/).
{
public:
	MyServer()
	{
		m_port = 8080;
	}


	~MyServer()
	{
		// none
	}

void setPort(unsigned short port)
{
	m_port = port;
}


protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(Poco::Util::OptionSet& options)
	{
		// none
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		// none
	}

	void displayHelp()
	{
		// none
	}

	int main(const std::vector<std::string>& args)
	{

			int maxQueued  = 100;

			int maxThreads = 16;

			HTTPServerParams* pParams = new HTTPServerParams;
			pParams->setMaxQueued(maxQueued);
			pParams->setMaxThreads(maxThreads);

			// set-up a server socket
			ServerSocket svs(m_port);
			// set-up a HTTPServer instance
			HTTPServer srv(new MyRequestHandlerFactory(), svs, pParams);
			// start the HTTPServer
			srv.start();
	std::cout << "listen port: " << m_port << std::endl;
			// wait for CTRL-C or kill
			waitForTerminationRequest();
			// Stop the HTTPServer
			srv.stop();

		return Application::EXIT_OK;
	}

private:
	unsigned short m_port;
};

