 /**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */


// display version


// TODO :
// use the latest libcurl
// in current built with pre-installed libcurl


#include <iostream>
#include <curlpp/cURLpp.hpp>


using namespace std;


/**
 * main
 */
int main(void)
{

    cout << "LIBCURLPP_VERSION: " <<  LIBCURLPP_VERSION << endl;
    cout << "libcurlVersion: " <<  curlpp::libcurlVersion() << endl;

	return EXIT_SUCCESS;
}


// g++ version.cpp -I/usr/local/Cellar/curlpp/0.8.1/include -L/usr/local/Cellar/curlpp/0.8.1/lib -lcurlpp
// LIBCURLPP_VERSION: 0.8.1
// libcurlVersion: libcurl/7.64.1 SecureTransport (LibreSSL/2.8.3) zlib/1.2.11 nghttp2/1.39.2


