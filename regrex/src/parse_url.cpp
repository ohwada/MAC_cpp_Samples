/**
 * parse_url.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ parse_url.cpp -std=c++11
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter03/problem_30/main.cpp

#include <iostream>
#include <string>
#include <regex>


/**
 * struct uri_parts
 */
struct uri_parts
{
   std::string  protocol;
   std::string  domain;
   int         port = 0;
   std::string  path;
   std::string  query;
   std::string  fragment;
};


/**
 * parse_url
 */
uri_parts parse_url(std::string url)
{
   std::regex rx(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");

   auto matches = std::smatch{};

   if (std::regex_match(url, matches, rx))
   {
      if (matches[1].matched && matches[2].matched)
      {
         uri_parts parts;
         parts.protocol = matches[1].str();
         parts.domain = matches[2].str();
         if(matches[4].matched)
            parts.port = std::stoi(matches[4]);
         if (matches[5].matched)
            parts.path = matches[5];
         if (matches[7].matched)
            parts.query = matches[7];
         if (matches[9].matched)
            parts.fragment = matches[9];

         return parts;
      }
   }

   return {};
}


/**
 * print_param
 */
void print_param(uri_parts p)
{
    int port = p.port;
    std::cout << "protocol: " << p.protocol << std::endl;
    std::cout << "domain: " << p.domain << std::endl;

    if(port > 0){
        std::cout << "port: " << port << std::endl;
    }

    std::cout << "path: " << p.path << std::endl;
    std::cout << "query: " << p.query << std::endl;
    std::cout << "fragment: " << p.fragment << std::endl;
}


/**
 * main
 */
int main()
{
   const std::string URL1("https://example.com");
   const std::string URL2("https://example.com:80/en/index.html?lite=true#abc");

// case 1
   auto p1 = parse_url(URL1);

    std::cout << URL1 << std::endl;
    print_param(p1);

// case 2
   auto p2 = parse_url(URL2);

    std::cout << URL2 << std::endl;
    print_param(p2);

    return 0;
}


//https://example.com:80/en/index.html?lite=true#abc
// protocol: https
// domain: example.com
// port: 80
// path: /en/index.html
// query: lite=true
//fragment: abc

