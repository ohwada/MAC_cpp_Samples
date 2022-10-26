/**
 *  http_get_form_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPFormServer/src/HTTPFormServer.cpp'

#include "Poco/Format.h"
#include "poco_http_server.hpp"
#include "form.hpp"


/**
 *  on_request
 */
void on_request(HTTPServerRequest& request, HTTPServerResponse& response)
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

    log_client(request);

    std::string method = request.getMethod();
    std::string uri = request.getURI();

    std::cout << "Method: " << method << std::endl;
    std::cout << "URI: " << uri << std::endl;

    std::string fpath("data/index_get.html");
    std::string mime("text/html");

    if( is_root(uri) ) {
        send_file(response, fpath,  mime);
        return;
    }

    std::string form = get_string_form(request);
    std::cout << "form: " << form << std::endl;

    std::string text;
    Poco::format(text, FORMAT,  method, uri, form);

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << text << std::endl;

	response.setContentType("text/html");

	std::ostream& ostr = response.send();
	ostr << text;
}


/**
 *  main
 */
int main(int argc, char** argv)
{
    unsigned short port = 9980;

	MyServer app;
    app.setPort(port);

	return app.run(argc, argv);
}
