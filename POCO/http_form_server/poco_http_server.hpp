#pragma once
/**
 *  htttp_server.hpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/MyServer/src/MyServer.cpp

#include <iostream>
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
void send_index_html(HTTPServerResponse& response);
void send_file(HTTPServerResponse& response, std::string fpath,  std::string mime);
bool is_root(HTTPServerRequest& request);
bool is_root(std::string uri);
void log_client(HTTPServerRequest& request);
void log_info(HTTPServerRequest& request, std::string msg);


/**
 *   log_client
 */
void log_client(HTTPServerRequest& request)
{
    std::string msg = std::string("Request from ") + request.clientAddress().toString();
    log_info(request, msg);
}


/**
 *  log_info
 */
void log_info(HTTPServerRequest& request, std::string msg)
{
	Application& app = Application::instance();
	app.logger().information(msg);
}


/**
 *  send_index_html
 */
void send_index_html(HTTPServerResponse& response)
{
    std::string fpath("data/index.html");
    std::string mime("text/html");
	send_file(response, fpath,  mime);
}


/**
 *  send_file
 */
void send_file(HTTPServerResponse& response, std::string fpath,  std::string mime)
{

	try{
		response.sendFile(fpath, mime);
	}
	catch(Poco::Exception e )
	{
		std::cerr << e.what() << std::endl;
	}
}


/**
 *  is_root
 */
bool is_root(HTTPServerRequest& request)
{
    return is_root( request.getURI() );
}


/**
 *  is_root
 */
bool is_root(std::string uri)
{
    const std::string SLASH("/");
    bool ret = (uri == SLASH)? true: false;
    return ret;
}


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
		return new MyRequestHandler();
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

