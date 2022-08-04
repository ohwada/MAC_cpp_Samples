/**
 *  parse_uri.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://master.url.cpp.al/url/ref/boost__urls__parse_uri.html

#include <iostream>
#include <boost/url/url_view.hpp>
#include <boost/url/src.hpp>


/**
 *  print_param
 */
void print_param(boost::system::result<boost::urls::url_view,
      boost::system::error_code> p)
{
std::cout << "scheme: " << p->scheme() << std::endl;
std::cout << "host: " << p->host() << std::endl;
std::cout << "port: " << p->port() << std::endl;
std::cout << "path: " << p->path() << std::endl;
std::cout << "query: " << p->query() << std::endl;
std::cout << " fragment: " << p->fragment() << std::endl;

}


/**
 *  main
 */
int main()
{
boost::urls::string_view uri1("https://www.example.com/path/to/file.txt?userid=1001&page=2&results=full");

boost::urls::string_view uri2("https://bbc.com:80/en/index.html?lite=true#ui");

	auto p1 = boost::urls::parse_uri(uri1);

std::cout << uri1 << std::endl;
print_param(p1);

	auto p2 = boost::urls::parse_uri(uri2);

std::cout << uri2 << std::endl;
print_param(p2);

return 0;
}

// https://www.example.com/path/to/file.txt?userid=1001&page=2&results=full
// scheme: https
// host: www.example.com
// port: 
// path: /path/to/file.txt
// query: userid=1001&page=2&results=full
 // fragment: 


