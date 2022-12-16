/**
 * ws_client.cpp
 * 2022-10-01 K.OHWADA
 */

// original : https://gist.github.com/tuxmartin/1218851b7e025f68ecc50f949c9dd332

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include <iostream>
#include "port.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{
    std::string host("localhost");
    unsigned short port = PORT;

    if(argc == 3) {
        host = argv[1];
      	port = std::atoi( argv[2] );
    } else if(argc == 2) {
      	port = std::atoi( argv[1] );
    } else {
        cout << "Usage: " << argv[0] << "[host] [port] [path] " << endl;
    }

    cout<< "host: " << host << endl;
    cout<< "port: " << port << endl;

   HTTPClientSession cs(host, port ); 

    HTTPRequest request(HTTPRequest::HTTP_GET, "/?encoding=text",HTTPMessage::HTTP_1_1);
    // request.set("origin", "http://www.websocket.org");
    HTTPResponse response;

    try {

        WebSocket* m_psock = new WebSocket(cs, request, response);
        char const *testStr="Hello echo websocket!";
        char receiveBuff[256];

        int len=m_psock->sendFrame(testStr,strlen(testStr),WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes " << len << std::endl;
        int flags=0;

        int rlen=m_psock->receiveFrame(receiveBuff,256,flags);
        std::cout << "Received bytes " << rlen << std::endl;
        std::cout << "r: " << receiveBuff << std::endl;

        m_psock->close();

    } catch (std::exception &e) {
        std::cout << "Exception " << e.what();
    }

}

// r: Hello echo websocket!
