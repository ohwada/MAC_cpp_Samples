#pragma once
/**
 *  poco_file_server.hpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/FileServer/src/FileServer.cpp

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
#include "Poco/File.h"
#include "Poco/Format.h"
#include "poco_file_sender.hpp"
#include "poco_server_util.hpp"


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
void on_request(HTTPServerRequest& request, HTTPServerResponse& response, std::string root);
Poco::File get_file( std::string dir, std::string uri);


/**
 * get_file
 */
Poco::File get_file( std::string dir, std::string uri)
{
	const std::string STR_SLASH("/");

	std::string fname;
	if( uri == STR_SLASH ) {
		fname = "index.html";
	} else {
		fname = uri;
	}

	return make_path(dir, fname);
}


/**
 *  class FileRequestHandler
 */
class FileRequestHandler: public HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
	FileRequestHandler(std::string root)
	{
// std::cout << "FileRequestHandler: " << root<< std::endl;
		m_root = root;
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		on_request(request, response, m_root);
	}

private:
	std::string m_root;
};


/**
 *  class FileRequestHandlerFactory
 */
class FileRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
FileRequestHandlerFactory(std::string root)
{
//std::cout << "FileRequestHandlerFactory: " << root<< std::endl;
		m_root = root;
}

HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
{
		const char SLASH = '/';
		std::string uri = request.getURI();

	//std::cout << "reateRequestHandler: " << uri << std::endl;

		if (uri[0] == SLASH)
			return new FileRequestHandler(m_root);
		else
			return 0;
	}

private:
	std::string m_root;
};


/**
 *  class FileServer
 */
// https://docs.pocoproject.org/current/Poco.Util.ServerApplication.html
class FileServer: public Poco::Util::ServerApplication
	/// The main application class.

	/// Youcan specify the port on which the server is listening (default
	/// 9980) and the format of the date/time string sent back to the client.
	///
	/// To test the TimeServer you can use any web browser (http://localhost:9980/).
{
public:
	FileServer()
	{
		m_port = 8080;
		m_root = std::string(".");
	}

	~FileServer()
	{
		// none
	}

void setPort(unsigned short port)
{
	m_port = port;
}

void setRoot(std::string root)
{
	m_root = root;
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

		unsigned short port = m_port;

			int maxQueued  = 100;

			int maxThreads = 16;

			HTTPServerParams* pParams = new HTTPServerParams;
			pParams->setMaxQueued(maxQueued);
			pParams->setMaxThreads(maxThreads);

			// set-up a server socket
			ServerSocket svs(port);
			// set-up a HTTPServer instance
			HTTPServer srv(new FileRequestHandlerFactory(m_root), svs, pParams);
			// start the HTTPServer
			srv.start();
	std::cout << "listen port: " << port << std::endl;
			// wait for CTRL-C or kill
			waitForTerminationRequest();
			// Stop the HTTPServer
			srv.stop();

		return Application::EXIT_OK;
	}

private:
	unsigned short m_port;
	std::string m_root;
};

