/**
 * hello_world.cpp
 * 2022-06-01 K.OHWADA
 */

// sample for router 
// "/" : return plain text
// "/html"  return HTML format
// "/json"  return JSON format


// original : https://github.com/Stiffstream/restinio/tree/master/dev/sample/hello_world

#include <iostream>

#include <restinio/all.hpp>


/**
 * init_resp
 */
template < typename RESP >
RESP
init_resp( RESP resp )
{
	resp.append_header( restinio::http_field::server, "RESTinio sample server /v.0.2" );
	resp.append_header_date_field();

	return resp;
}

using router_t = restinio::router::express_router_t<>;


/**
 * create_request_handler
 */
auto create_request_handler()
{
	auto router = std::make_unique< router_t >();

	router->http_get(
		"/",
		[]( auto req, auto ){
				init_resp( req->create_response() )
					.append_header( restinio::http_field::content_type, "text/plain; charset=utf-8" )
					.set_body( "Hello world!")
					.done();

				return restinio::request_accepted();
		} );

	router->http_get(
		"/json",
		[]( auto req, auto ){
				init_resp( req->create_response() )
					.append_header( restinio::http_field::content_type, "application/json" )
					.set_body( R"-({"message" : "Hello world!"})-")
					.done();

				return restinio::request_accepted();
		} );

	router->http_get(
		"/html",
		[]( auto req, auto ){
				init_resp( req->create_response() )
						.append_header( restinio::http_field::content_type, "text/html; charset=utf-8" )
						.set_body(
							"<html>\r\n"
							"  <head><title>Hello from RESTinio!</title></head>\r\n"
							"  <body>\r\n"
							"    <center><h1>Hello world</h1></center>\r\n"
							"  </body>\r\n"
							"</html>\r\n" )
						.done();

				return restinio::request_accepted();
		} );

	return router;
}


/**
 * run_server
 */
bool run_server(unsigned short port)
{
	using namespace std::chrono;

	try
	{
		using traits_t =
			restinio::traits_t<
				restinio::asio_timer_manager_t,
				restinio::single_threaded_ostream_logger_t,
				router_t >;
		restinio::run(
			restinio::on_this_thread<traits_t>()
				.port( port )
				.address( "localhost" )
				.request_handler( create_request_handler() ) );
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
