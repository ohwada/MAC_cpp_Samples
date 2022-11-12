#pragma once
/**
 *  upload_response_builder.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include <fmt/core.h>

// prototype
std::string build_response(std::string fname);


/**
 *  build_response
 */
std::string build_response(std::string fname)
{
    std::string FORMAT=
R"(<html>
<head>
<title>RESTinio Server demo</title>
</head>
<body>
<h1> RESTinio File Upload demo </h1>
<a href="/">[HOME]</a> <br/>
<h2>Uploaded</h2>
<font size="+2">
<a href="{:s}"> {:s} </a>
</font>
</body>
</html>)";

    std::string text =
     fmt::format(FORMAT,  fname, fname);

    return text;
}
