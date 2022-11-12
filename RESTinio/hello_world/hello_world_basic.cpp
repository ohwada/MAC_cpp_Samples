/**
 * hello_world_basic.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/Stiffstream/restinio/tree/master/dev/sample/hello_world_basic

#include <iostream>
#include <restinio/all.hpp>


/**
 * handler
 */
// Create request handler.
restinio::request_handling_status_t handler( const restinio::request_handle_t& req )
{
	if( restinio::http_method_get() == req->header().method() &&
		req->header().request_target() == "/" )
	{
		req->create_response()
			.append_header( restinio::http_field::server, "RESTinio hello world server" )
			.append_header_date_field()
			.append_header( restinio::http_field::content_type, "text/plain; charset=utf-8" )
			.set_body( fmt::format(
					RESTINIO_FMT_FORMAT_STRING( "{}: Hello world basic" ),
					restinio::fmtlib_tools::streamed( req->remote_endpoint() ) ) )
			.done();

		return restinio::request_accepted();
	}

	return restinio::request_rejected();
}


/**
 * run_server
 */
bool run_server(unsigned short port)
{

	try
	{
	std::cout << "listen port: " << port << std::endl;
		restinio::run(
			restinio::on_thread_pool( std::thread::hardware_concurrency() )
				.port( port )
				.address( "localhost" )
				.request_handler( handler ) );
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return false;
	}

	return true;
}


/**
 * main
 */
int main()
{
	unsigned short port = 8080;

	run_server(port);

	return 0;
}
