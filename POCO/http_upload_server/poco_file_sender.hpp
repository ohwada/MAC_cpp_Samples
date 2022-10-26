#pragma once
/**
 *  poco_file_sender.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Format.h"
#include "poco_mime.hpp"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;


// prototype
void send_file(HTTPServerResponse& response, Poco::File file);
void send_file(HTTPServerResponse& response, std::string fpath);
void send_file_mime(HTTPServerResponse& response, std::string fpath,  std::string mime);
void send_notfound(
Poco::Net::HTTPServerResponse& response, std::string uri);
std::string build_msg_notfound( std::string uri);
Poco::File  make_path(std::string dir, std::string fname);
Poco::File make_path(Poco::Path parent, std::string fname);


/**
 *  send_file
 */
void send_file(HTTPServerResponse& response, std::string fpath)
{
    Poco::File file(fpath);
    send_file(response, file);
}


/**
 *  send_file
 */
void send_file(HTTPServerResponse& response, Poco::File file)
{
    std::string fpath = file.path();
    std::string mime = get_mime(file);
    send_file_mime(response, fpath,  mime);
}


/**
 *  send_file_mime
 */
void send_file_mime(HTTPServerResponse& response, std::string fpath,  std::string mime)
{

	try{
		response.sendFile(fpath, mime);
	}
	catch(Poco::Exception e )
	{
		std::cerr << e.what() << " : " << fpath << std::endl;
	}
}



/**
 *  send_notfound
 */
void send_notfound(
Poco::Net::HTTPServerResponse& response, std::string uri)
{

    std::string text = build_msg_notfound(uri);

	response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);

	response.setContentType("text/html");

		std::ostream& ostr = response.send();
		ostr << text;
}


/**
 *  biuld_msg_notfound
 */
std::string build_msg_notfound( std::string uri)
{

    std::string FORMAT = 
R"(<html><head>
<title>POCO HTTP Server</title>
	</head><body>
<h2>Not Found File</h2>
<font size="+2">%s</font>
</body></html>)";

        std::string text = Poco::format( FORMAT, uri);
        return text;
}


/**
 * make_path
 */
Poco::File  make_path(std::string dir, std::string fname1)
{
    const char SLASH = '/';

    Poco::Path parent(dir);

    std::string fname2;
    if( fname1[0] == SLASH){
        fname2 = &fname1[1];
    } else {
        fname2 = fname1;
    }

    return make_path(parent, fname2);
}

/**
 * make_path
 */
Poco::File make_path(Poco::Path parent, std::string fname)
{
    Poco::Path path(parent, fname);
    Poco::File file( path.toString() );
    return file;
}
