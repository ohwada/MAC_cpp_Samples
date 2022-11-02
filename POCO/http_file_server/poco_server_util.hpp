#pragma once
/**
 *  poco_server_util.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Format.h"


using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::Application;


// prototype
bool is_get(HTTPServerRequest& request);
bool is_get(std::string method);
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
 *  is_get
 */
bool is_get(HTTPServerRequest& request)
{
    return is_get( request.getMethod() );
}


/**
 *  is_get
 */
bool is_get(std::string method)
{
    const std::string GET("GET");
    bool ret = (method == GET)? true: false;
    return ret;
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

