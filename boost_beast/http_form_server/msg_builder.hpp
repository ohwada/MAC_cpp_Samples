#pragma once
/**
 * msg_builder.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include <boost/format.hpp>


// prototype
std::string build_msg_not_found( std::string target);
std::string build_msg_server_error( std::string what);
std::string build_msg_from(std::string method, std::string key, std::string value);


/**
 * build_msg_not_found
 */
std::string build_msg_not_found( std::string target)
{
    const std::string FORMAT("The resource '%s' was not found.");
    std::string msg = 
    boost::str( boost::format(FORMAT) % target);
    return msg;
}


/**
 *  build_msg_server_error
 */
std::string build_msg_server_error( std::string what)
{
    std::string FORMAT = R"(An error occurred: '%s')";
    std::string msg =
    boost::str( boost::format(FORMAT) % what );
    return msg;
}


/**
 *  build_msg_form
 */
std::string build_msg_form(std::string method, std::string key, std::string value)
{

std::string FORMAT = R"(
<h1>Form Server demo<h1>
<h2>method= %s<h2>
<font size="+2">
key= %s, value= %s <br/>
</font>
)" ;

    std::string msg = 
    boost::str( boost::format(FORMAT) % method % key % value);

return msg;
}
