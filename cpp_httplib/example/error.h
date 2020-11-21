/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// print error
#include "httplib.h"

// prototype
void printError( httplib::Error code);
std::string getError( httplib::Error code );

/**
 * printError
 */
void printError( httplib::Error code)
{
   std::string err = getError( code );
    fprintf(stderr, "Error: %s (%d) \n", (char *)err.c_str(), (int)code );
}

/**
 * getError
 */
std::string getError( httplib::Error code )
{
    std::string str;

switch(code)
{
case httplib::Success:
    str = "Success";
    break;
case httplib::Unknown:
    str = "Unkonwn";
    break;
case httplib::Connection:
    str = "ConnectionConnection";
    break;
case httplib::BindIPAddress:
    str = "BindIPAddress";
    break;
case httplib::Read:
    str = "Read";
    break;
case httplib::Write:
    str = "Write";
    break;
case httplib::ExceedRedirectCount:
    str = "ExceedRedirectCount";
    break;
case httplib::Canceled:
    str = "Canceled";
    break;
case httplib::SSLConnection:
    str = "SSLConnection";
    break;
case httplib::SSLLoadingCerts:
    str = "SSLLoadingCerts";
    break;
case httplib::SSLServerVerification:
    str = "SSLServerVerification";
    break;
case httplib::UnsupportedMultipartBoundaryChars:
    str = "UnsupportedMultipartBoundaryChars";
    break;
}

return str;
}
