 #pragma once
/**
 * response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include <fmt/core.h>

// prototype
 std::string build_msg_uploaded(std::string fname);
std::string build_msg_not_found( std::string path);


/**
 *  build_msg_uploaded
 */
std::string build_msg_uploaded(std::string fname)
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


/**
 *  biuld_msg_notfound
 */
std::string build_msg_not_found( std::string path)
{

    std::string FORMAT = 
R"(<html><head>
<title> RESTinio Server </title>
	</head><body>
<h2>Not Found File</h2>
<font size="+2"> {:s} </font>
</body></html>)";

    std::string text =
     fmt::format(FORMAT,  path);
        return text;
}

