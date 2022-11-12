/**
 * query_string_params.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/Stiffstream/restinio/tree/master/dev/sample/query_string_params

#include <iostream>
#include <sstream>
#include <iterator>
#include <restinio/all.hpp>
 #include "response_builder.hpp"
#include "response_sender.hpp"



/**
 * handler
 */
// Create request handler.
restinio::request_handling_status_t handler( const restinio::request_handle_t& req )
{
	if( restinio::http_method_get() == req->header().method() )
	{
		auto path = req->header().path();
		std::cout << "path: " << path << std::endl;

		auto target = req->header().request_target();
		std::cout << "target: " << target << std::endl;

	if(target == "/"){
		std::string file_path("www/index.html");
		std::string content_type("text/html");
		return send_file(req, file_path, content_type);
	}

		fmt::basic_memory_buffer< char, 1u > response_body;
		auto response_body_inserter = std::back_inserter( response_body );

		std::string str_query;

		fmt::format_to( response_body_inserter,
				RESTINIO_FMT_FORMAT_STRING( "GET request to '{}'\n" ),
				req->header().request_target() );

		// Request header fields.
		fmt::format_to( response_body_inserter,
				RESTINIO_FMT_FORMAT_STRING( "HTTP-fields ({}):\n" ),
				req->header().fields_count() );
		for( const auto & f : req->header() )
		{
			fmt::format_to( response_body_inserter,
					RESTINIO_FMT_FORMAT_STRING( "{}: {}\n" ),
					f.name(), f.value() );
		}

		// Query params.
		const auto qp = restinio::parse_query( req->header().query() );

		if( qp.empty() )
		{
			fmt::format_to( response_body_inserter,
					RESTINIO_FMT_FORMAT_STRING( "No query parameters." ) );

			str_query =  "No query parameters. <br/> \n";

		}
		else
		{
				fmt::format_to( response_body_inserter,
					RESTINIO_FMT_FORMAT_STRING( "Query params ({}):\n" ), qp.size() );

			std::stringstream ss;

			for(auto p : qp )
			{
		fmt::format_to( response_body_inserter,
						RESTINIO_FMT_FORMAT_STRING( "'{}' => '{}'\n" ),
						restinio::fmtlib_tools::streamed( p.first ),
						restinio::fmtlib_tools::streamed( p.second ) );
				ss << p.first << " : " << p.second << " <br/>\n";
			} // for

			str_query += ss.str();
		}

		//if( qp.has( "debug" ) && qp[ "debug" ] == "true" )
	
			std::cout << std::endl;	
			std::cout << "request" << std::endl;
			std::cout.write( response_body.data(), response_body.size() );
			std::cout << std::flush;
	
		std::cout << std::endl;
		std::cout << "response" << std::endl;
		std::cout << str_query << std::endl;

		 std::string text= build_msg_query(str_query);

		std::cout << text << std::endl;

		std::string content_type("text/html");

		return send_text(req, text, content_type);
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
