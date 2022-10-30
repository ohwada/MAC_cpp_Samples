/**
 *  form_response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "Poco/Format.h"

// prototype
std::string build_response( std::string method, std::string uri, std::string form);


/**
 *  build_response
 */
std::string build_response( std::string method, std::string uri, std::string form)
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
<h2>Form</h2>
<p> %s </p>
</body>
</html>)";

    std::string text;
    Poco::format(text, FORMAT,  method, uri, form);

    return text;
}

