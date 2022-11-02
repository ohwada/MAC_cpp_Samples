#pragma once
/**
 * form.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include<regex>
#include <boost/format.hpp>

// prototype
bool parse_request_path(std::string request, std::string &key, std::string &value);
std::string build_msg_form(std::string method, std::string key, std::string value);

/**
 *  parse_request
 */
bool parse_request_path(std::string request, std::string &key, std::string &value)
{

    std::string str = R"((\w+)=(\w+))";

    std::regex reg(str);

    std::smatch m;

    if (std::regex_search(request, m, reg)) 
    {
        key = m[1].str();
        value = m[2].str();
    } else {
        return false;
    }

    return true;
}


/**
 *  build_msg_form
 */
std::string build_msg_form(std::string method, std::string key, std::string value)
{

std::string FORMAT = R"(
<html><head>
<title>Form Server demo</title>
</head><body>
<h1>Form Server demo</h1>
<a href="/">[HOME]</a><br/>
<h2>method= %s</h2>
<font size="+2">
key= %s, value= %s <br/>
</font>
</body></html>
)" ;

    std::string msg = 
    boost::str( boost::format(FORMAT) % method % key % value);

return msg;
}

