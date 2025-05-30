/**
 *  parse_response.cpp
 * 2020-07-01 K.OHWADA
 */

// https://github.com/nekipelov/httpparser

#include <iostream>
#include <httpparser/response.h>
#include <httpparser/httpresponseparser.h>

using namespace httpparser;


/**
 *  main
 */
int main(int, char**)
{
    const char text[] =
            "HTTP/1.1 200 OK\r\n"
            "Server: nginx/1.2.1\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 8\r\n"
            "Connection: keep-alive\r\n"
            "\r\n"
            "<html />";

    Response response;
    HttpResponseParser parser;

    HttpResponseParser::ParseResult res = parser.parse(response, text, text + strlen(text));

    if( res == HttpResponseParser::ParsingCompleted )
    {
        std::cout << response.inspect() << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        std::cerr << "Parsing failed" << std::endl;
        return EXIT_FAILURE;
    }
}
