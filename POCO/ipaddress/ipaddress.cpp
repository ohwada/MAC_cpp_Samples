/**
 * ipaddress.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://poco.roundsquare.net/2011/03/13/poconetdns/

#include <iostream>
#include <string>
#include <vector>
#include <Poco/Net/DNS.h>
#include <Poco/Net/IPAddress.h>
#include <Poco/Net/NetException.h>


/**
 *  get_ipaddress
 */
bool get_ipaddress( std::string hostname,  std::vector<std::string> &vec, std::string &error)
{

	bool is_error = false;

try
{

	auto addresses = Poco::Net::DNS::hostByName(hostname).addresses();

	for(auto address: addresses)
	{
		Poco::Net::IPAddress ipaddress(address);
		if ( ipaddress.isV4() ) {
			auto addr = ipaddress.toString();
			vec.push_back(addr);
		}
	} // for

}
catch(Poco::Net::HostNotFoundException e)
{
		is_error = true;
		error = e.what();
}
catch(Poco::Net::NoAddressFoundException e)
{
		is_error = true;
		error = e.what();
}
catch(Poco::Net::DNSException e)
{
        is_error = true;
		error = e.what();
}
catch(Poco::IOException e)
{
       	is_error = true;
		error = e.what();
}

	return 		!is_error;
}


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[]) 
{

    string hostname("example.com");

	// const std::string hostname("packtpub.com");

   if (argc == 2) {
        hostname = argv[1];
    } else {
        cout << "Usage: " << argv[0]  << "[hostname] " << endl;
    }

	cout << hostname << endl;

	vector<string> vec;
	string error;

	auto ret = get_ipaddress(hostname, vec,  error);
	if(!ret) {
		cerr << "cannot get ipaddress: " << error << endl;
	    return EXIT_FAILURE;
	}

	cout << "found: " <<  vec.size() << endl;

	for(auto ip: vec){
		cout << ip << endl;
	}

 	return EXIT_SUCCESS;
}

// example.com
// found: 1
// 93.184.216.34
