/**
 *  http_client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://mcommit.hatenadiary.com/entry/2017/07/14/170146#HTTPS%E9%80%9A%E4%BF%A1%E3%81%AE%E3%82%B3%E3%83%BC%E3%83%89%E3%82%92%E6%9B%B8%E3%81%84%E3%81%A6%E3%81%BF%E3%82%8B

#include <string>
#include <iostream>
#include <sstream>

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

using namespace std;


/**
 *  main
 */
int main(int argc, char **argv)
{

	std::string host("example.com");
	int port = 80;
	std::string path("/");

    if(argc == 4) {
      	host = argv[1];
      	port = atoi( argv[2] );
      	path = argv[3];
    } else if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        cerr << "Usage: " << argv[0] << " [host] [port]  [path]" << endl;
    }

    cerr << "host: " << host << endl;
    cerr << "port: " << port << endl;
    cerr << "path: " << path << endl;

	try {
		Poco::Net::HTTPClientSession session(host, port);

		Poco::Net::HTTPRequest req("GET", path, Poco::Net::HTTPMessage::HTTP_1_1);

		// send request
		session.sendRequest(req);

		// recieve response
		Poco::Net::HTTPResponse res;
		istream& rs = session.receiveResponse(res);

		stringstream sstr;
		Poco::StreamCopier::copyStream(rs, sstr);
		string response = sstr.str();
		cout << string("response:") + response << endl;
	}
	catch ( Poco::Exception& ex )
	{
		string msg = string("Poco Exception : ") + ex.what() + ", message: " + ex.message();
		cout << msg << endl;
   	 	return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

