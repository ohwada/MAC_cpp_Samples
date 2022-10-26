/**
 * https_client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://mcommit.hatenadiary.com/entry/2017/07/14/170146
// https://docs.pocoproject.org/current/Poco.Net.HTTPSClientSession.html

#include <string>
#include <iostream>
#include <sstream>

#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include "Poco/Net/Context.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/AcceptCertificateHandler.h"

/**
 * https_client
 */
bool https_client(std::string host,  Poco::UInt16 port,  std::string path, std::string &response)
{

bool is_error = false;

// SSL connection information initialization
    Poco::Net::initializeSSL();

    Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler ( new Poco::Net::AcceptCertificateHandler(false) );
    Poco::Net::Context::Ptr ptrContext ( new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "") );
    Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);

    try {
        Poco::Net::HTTPSClientSession session(host, port);
        Poco::Net::HTTPRequest req("GET", path, Poco::Net::HTTPMessage::HTTP_1_1);

    // send request
        session.sendRequest(req);

    // recieve response
        Poco::Net::HTTPResponse res;
        istream& rs = session.receiveResponse(res);

        stringstream sstr;
        Poco::StreamCopier::copyStream(rs, sstr);
        response = sstr.str();
    }
    catch ( Poco::Exception& ex )
    {
        string msg = string("Poco Exception : ") + ex.what() + ", message: " + ex.message();
        dtd::cout << msg << std::endl;
        is_error = true;
    }

    return !is_error;
}

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{
    std::string host("example.com");

    Poco::UInt16 port = 443;

   string path("/");

    string response;

    https_client(host,  port,  path, response);

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    return 0;
}

