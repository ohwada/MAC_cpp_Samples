#pragma once
/**
 *  upload_response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include "Poco/Format.h"

// prototype
std::string build_response(std::string method, std::string uri, std::string name, std::string type, std::string filename, int length);


/**
 *  build_response
 */
std::string build_response(std::string method, std::string uri, std::string name, std::string type, std::string filename, int length)
{
    std::string FORMAT=
R"(<html>
<head>
<title>HTTP Server demo</title>
</head>
<body>
<h2>POCO Form Server demo</h2>
<a href="/">[HOME]</a> <br/>
<h2>Request</h2>
<p>
Method: %s <br/>
URI: %s <br/>
</p>
<h2>Upload</h2>
<p>
Name: %s <br/>
File Name: %s <br/>
Type: %s <br/>
Size: %d <br/>
</p>
<font size="+2">
<a href = "%s"> %s </a>
</font>
</body>
</html>)";


std::cout << "Name: " << name << std::endl;
std::cout << "File Name: " << filename << std::endl;
std::cout << "Type: " << type << std::endl;
std::cout << "Size: " << length << std::endl;

std::string text;

    Poco::format(text, FORMAT,  method, uri, name, filename, type, length, filename, filename);

    return text;
}
