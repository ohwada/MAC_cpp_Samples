/**
 *  parse_url.cpp
 * 2022-06-01 K.OHWADA
 */


// reference ; http://think-async.com/Urdl/doc/html/urdl/reference/core/url.html


#include <iostream>
#include <string>
#include <urdl/url.hpp>
#include <urdl/impl/url.ipp>


/**
 *  main
 */
int main()
{
const std::string TEXT("http://user:pass@example.com:1234/dir/page?param=0#anchor");
urdl::url url(TEXT);

std::cout << TEXT << std::endl;
std::cout << "Protocol: " << url.protocol() << std::endl;
std::cout << "User Info: " << url.user_info() << std::endl;
std::cout << "Host: " << url.host() << std::endl;
std::cout << "Port: " << url.port() << std::endl;
std::cout << "Path: " << url.path() << std::endl;
std::cout << "Query: " << url.query() << std::endl;
std::cout << "Fragment: " << url.fragment() << std::endl;

return 0;
}


// http://user:pass@example.com:1234/dir/page?param=0#anchor
// Protocol: http
// User Info: user:pass
// Host: example.com
// Port: 1234
// Path: /dir/page
// Query: param=0
// Fragment: anchor

