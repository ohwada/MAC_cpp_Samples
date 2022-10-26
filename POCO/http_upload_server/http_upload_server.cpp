/**
 *  http_upload_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPTimeServer/src/HTTPTimeServer.cpp


#include "poco_http_server.hpp"
#include "poco_file_sender.hpp"
#include "poco_server_util.hpp"
#include "MyPartHandler.hpp"
#include "poco_file_stream.hpp"
#include "upload_response_builder.hpp"

const std::string DIR_UPLOAD("upload");


/**
 *  send_index_html
 */
void send_index_html(HTTPServerResponse& response)
{
    Poco::File file("www/index.html");
    std::cout<< file.path() << std::endl;
    send_file(response, file);
}


/**
 *  send_file_uri
 */
void send_file_uri(HTTPServerResponse& response,  std::string uri)
{
        Poco::File file = make_path( DIR_UPLOAD, uri );
        std::cout<< file.path() << std::endl;
	    if ( file.exists() && file.isFile() ) {
              send_file(response, file);
        } else {
	          send_notfound(response, uri);
        }
}



/**
 *  on_request
 */
void on_request(HTTPServerRequest& request, HTTPServerResponse& response)
{

    log_client(request);

    std::string method = request.getMethod();
    std::string uri = request.getURI();

    std::cout << "Method: " << method << std::endl;
    std::cout << "URI: " << uri << std::endl;

    if( is_get(method) ) {
        if( is_root(uri) ) {
            send_index_html(response);
        } else {
            send_file_uri(response,  uri);
        } // is_root
        return;
} // if is_get

    MyPartHandler partHandler;
    HTMLForm form(request, request.stream(), partHandler);

    std::string response_text;

if (!partHandler.name().empty())
{

    std::string name = partHandler.name();
    std::string type = partHandler.contentType();
    std::string filename = partHandler.fileName();
    int length = partHandler.length();
    std::string data = partHandler.data();

    response_text = build_response(method, uri, name, type, filename, length);

    Poco::File file = make_path(DIR_UPLOAD, filename);
    std::string path = file.path();

    bool ret = file_binary_write(path, data, (size_t)length);
    if(ret){
        std::cout << "saved: " << path << std::endl;
    }

} // if partHandler

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << response_text << std::endl;

	response.setContentType("text/html");

	std::ostream& ostr = response.send();
	ostr << response_text;
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
