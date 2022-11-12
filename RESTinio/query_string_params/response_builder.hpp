 #pragma once
/**
 * response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include <fmt/core.h>

// prototype
 std::string build_msg_query(std::string query);


/**
 *  build_msg_query
 */
std::string build_msg_query(std::string query)
{
    std::string FORMAT=
R"(<html>
<head>
<title>RESTinio Server</title>
</head>
<body>
<h1> RESTinio Server demo </h1>
<a href="/">[HOME]</a> <br/>
<h2>Query String</h2>
<font size="+2">
{:s}
</font>
</body>
</html>)";

    std::string text =
     fmt::format(FORMAT,  query);

    return text;
}
