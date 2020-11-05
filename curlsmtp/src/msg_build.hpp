/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail to Gmail SMTP server 


#include <string>
#include <cstdio>

// prototype
std::string getDefaultMessage(void);
char* getCurlVersion(void);

// constant
const std::string CRLF("\r\n");


/**
 * getDefaultMessage
 */
std::string getDefaultMessage(void)
{
   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

	const std::string MSG1("This is a test e-mail.");
 	const std::string MSG2( "This mail was sent using CurlSmtp");

    snprintf(buf, BUFSIZE, "and %s", getCurlVersion() );
	const std::string MSG3( buf );

    std::string msg = 
    MSG1 + CRLF
    + MSG2 + CRLF
    + MSG3 + CRLF;

	return msg;
}


/**
 * getCurlVersion
 */
char* getCurlVersion(void)
{
    const size_t BUFSIZE = 100;
    static char buff[BUFSIZE];
    snprintf( buff, BUFSIZE, "libcurl %s",  LIBCURL_VERSION );
    return buff;
}


