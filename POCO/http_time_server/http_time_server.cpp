/**
 *  http_time_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPTimeServer/src/HTTPTimeServer.cpp
// reference : https://codezine.jp/article/detail/1792?p=2&anchor=3

//
// HTTPTimeServer.cpp
//
// This sample demonstrates the HTTPServer and related classes.
//

#include "Poco/Format.h"
#include "poco_time_server.hpp"


/**
 *  on_request
 */
void on_request(HTTPServerRequest& request, HTTPServerResponse& response, std::string format)
{
	std::string FORMAT =
R"(<html><head>
<title>HTTPTimeServer powered by POCO C++ Libraries</title>
<meta http-equiv="refresh" content="%d">
</head><body>
<p style="text-align: center; font-size: 48px;">%s</p>
</body></html>)";

	Application& app = Application::instance();
	app.logger().information("Request from " + request.clientAddress().toString());

	Timestamp now;
	std::string dt(DateTimeFormatter::format(now, format));

	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

    int refresh_time = 1; // 1sec
	std::string text = Poco::format( FORMAT, refresh_time, dt);

	std::ostream& ostr = response.send();
	ostr << text;
}


/**
 *  main
 */
int main(int argc, char** argv)
{
    unsigned short port = 9980;

	TimeServer app;
    app.setPort(port);
    app.setFormat(DateTimeFormat::SORTABLE_FORMAT);

	return app.run(argc, argv);
}
