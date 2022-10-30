/**
 *  local_server.cpp
 * 2022-06-01 K.OHWADA
 */


#include "poco_http_server.hpp"
#include "poco_request_saver.hpp"
#include "poco_request_parser.hpp"
#include "poco_response_builder.hpp"
#include "oauth_request_builder.hpp"
#include "oauth_request_refresh_token.hpp"
#include "config.hpp"

// global
bool is_debug = false;


/**
 *  on_listen
 */
void on_listen()
{
    std::string auth_url;
    std::string error;

    bool ret1 = buildAuthorizationCodeUrlClient(SCOPE_MAIL, PORT, auth_url, error);
    if( !ret1 ){
        std::cerr << "buildAuthorizationCodeUrlClient: " << error << std::endl;
        return;
    }

// enter manually
    printEnterUrl(auth_url);
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

    bool is_verbose = true;
    save_request(request, is_verbose );

    std::string fpath("www/index.html");
    std::string mime("text/html");

    if( is_root(uri) ) {
        send_file(response, fpath,  mime);
        return;
    }

std::string code;
std::string scope;

bool ret1 = parse_request(request, code, scope);

        std::cout << "code: " << code << std::endl;
        std::cout << "scope: " << scope << std::endl;

    std::string text = build_response(code, scope);

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << text << std::endl;

	response.setContentType("text/html");

	std::ostream& ostr = response.send();
	ostr << text;

    if(is_debug){
        return;
    }

    if(ret1){
        sendRequestRefreshToken(code, scope);
    }

}


/**
 *  main
 */
int main(int argc, char** argv)
{

    if(argc == 2) {
      	is_debug = (bool)atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s  [debug] \n",  argv[0] );
    }

    if( is_debug ) {
        printf("debug mode \n");
    }

	MyServer app;
    app.setPort(PORT);

	return app.run(argc, argv);
}
