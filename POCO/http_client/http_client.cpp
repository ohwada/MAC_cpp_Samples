/**
 * http_client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://tullio.hatenablog.com/entry/20090430/1241102742
// https://docs.pocoproject.org/current/Poco.Net.HTTPClientSession.html

#include <iostream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
 #include <Poco/Net/NetException.h>


/**
 * http_client
 */
bool http_client(std::string host,  Poco::UInt16 port,  std::string uri, std::string &body)
{

    bool is_error = false;

try {

// set Access host and port
  Poco::Net::HTTPClientSession 
client(host,port);

// set request
  Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri); 
 
    std::cout << "request" << std::endl;
    request.write(std::cout);

// Preparing to receive response
  Poco::Net::HTTPResponse response;

// send request
    client.sendRequest(request);

// get response
  std::istream &res =  client.receiveResponse(response); 

// get the Content-Length of the header
  int len = response.getContentLength();

// Allocate an area to put the body HTML
  char *resbody = new char[len+1];
 
// output HTTP headers
    std::cout << std::endl;
    std::cout << "header" << std::endl;
    response.write(std::cout);  

// get HTML body
    res.read(resbody,len);  
    body = resbody;

} catch(Poco::Net::HostNotFoundException e) {
    std::cerr << e.displayText() << std::endl;
    is_error = true;
} catch( Poco::Net::ConnectionRefusedException e){
    std::cerr << e.displayText() << std::endl;
    is_error = true;
}

    return !is_error;
}


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    std::string host("example.com");

    Poco::UInt16 port = 80;

    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [host] [port] " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;

    string uri("/");

    string body;

    http_client(host,  port,  uri, body);

    cout << endl;
    cout << "body" << endl;
    cout << body << endl;

  return 0;
}