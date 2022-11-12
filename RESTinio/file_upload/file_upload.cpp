 /**
 * file_upload.cpp
 * 2022-06-01 K.OHWADA
 */

//	Simple example that shows file upload functionality.
// original : https://github.com/Stiffstream/restinio/tree/master/dev/sample/file_upload

#include <iostream>
#include <random>
#include <fstream>

#include <restinio/all.hpp>

#include <restinio/helpers/file_upload.hpp>

#include <clara.hpp>
#include <fmt/format.h>

#include "content_type.hpp"
#include "response_builder.hpp"
#include "response_sender.hpp"
#include "file_util.hpp"


 /**
 * struct app_args_t
 */
struct app_args_t
{
	bool m_help{ false };
	std::string m_dest_folder{ "upload" };
	std::string m_address{ "localhost" };
	std::uint16_t m_port{ 8080 };
	std::size_t m_pool_size{ 1 };
	bool m_trace_server{ false };


 /**
 * parse
 */
	static app_args_t
	parse( int argc, const char * argv[] )
	{
		using namespace clara;

		app_args_t result;

		auto cli =
			Opt( result.m_dest_folder, "destination folder" )
					["-d"]["--dest-folder"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"destination folder for uploaded files"
								" (default: {})" ), result.m_dest_folder ) )
			| Opt( result.m_address, "address" )
					["-a"]["--address"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"address to listen (default: {})" ),
							result.m_address ) )
			| Opt( result.m_port, "port" )
					["-p"]["--port"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"port to listen (default: {})" ),
							result.m_port ) )
			| Opt( result.m_pool_size, "thread-pool size" )
					[ "-n" ][ "--thread-pool-size" ]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"The size of a thread pool to run server (default: {})" ),
							result.m_pool_size ) )
			| Opt( result.m_trace_server )
					[ "-t" ][ "--trace" ]
					( "Enable trace server" )
			| Help(result.m_help);

		auto parse_result = cli.parse( Args(argc, argv) );
		if( !parse_result )
		{
			throw std::runtime_error{
				fmt::format(
					RESTINIO_FMT_FORMAT_STRING(
						"Invalid command-line arguments: {}" ),
					parse_result.errorMessage() ) };
		}

		if( result.m_help )
		{
			std::cout << cli << std::endl;
		}

		return result;
	}
};

using router_t = restinio::router::express_router_t<>;


 /**
 * store_file_to_disk
 */
void store_file_to_disk(
	const app_args_t & args,
	restinio::string_view_t file_name,
	restinio::string_view_t raw_content )
{
	std::ofstream dest_file;
	dest_file.exceptions( std::ofstream::failbit );
	dest_file.open(
			fmt::format( RESTINIO_FMT_FORMAT_STRING( "{}/{}" ),
					restinio::fmtlib_tools::streamed( args.m_dest_folder ),
					restinio::fmtlib_tools::streamed( file_name ) ),
			std::ios_base::out | std::ios_base::trunc | std::ios_base::binary );
	dest_file.write( raw_content.data(), raw_content.size() );
}


 /**
 * save_file
 */
	std::string save_file(
	const app_args_t & args,
	const restinio::request_handle_t & req )
{
	using namespace restinio::file_upload;

	std::string fname;

	const auto enumeration_result = enumerate_parts_with_files(
			*req,
			[&args, &fname]( const part_description_t & part ) {
				if( "file" == part.name )
				{
					// We can handle the name only in 'filename' parameter.
					if( part.filename )
					{
						// NOTE: the validity of filename is not checked.
						// This is just for simplification of the example.
						fname = std::string(*part.filename);
						store_file_to_disk( args, *part.filename, part.body );
						// There is no need to handle other parts.
						return handling_result_t::stop_enumeration;
					}
				}

				// We expect only one part with name 'file'.
				// So if that part is not found yet there is some error
				// and there is no need to continue.
				return handling_result_t::terminate_enumeration;
			} );

	if( !enumeration_result || 1u != *enumeration_result ){
		throw std::runtime_error( "file content not found!" );
	}

	return fname;
}


 /**
 * make_router
 */
auto make_router( const app_args_t & args )
{
	auto router = std::make_unique< router_t >();

	router->http_get(
		"/",
		[ & ]( const restinio::request_handle_t& req, auto ){
			std::string file_path("www/index.html");
			std::string content_type("text/html");
			return send_file(req, file_path, content_type);
		} );

	router->http_get(
		R"(/:path(.*)\.:ext(.*))",
		restinio::path2regex::options_t{}.strict( true ),
		[&]( auto req, auto params ){
		auto ext = params[ "ext" ];
		auto content_type = 	content_type_by_file_extention(ext);
		std::cout << "ext: " <<  ext << std::endl;
		std::cout << "content_type: " <<  content_type << std::endl;

		auto path = req->header().path();
			std::cout << "header path: " << path << std::endl;

			std::string str_path = 
			std::string{ path.data(), path.size() };

			std::cout << "str_path: " << str_path << std::endl;

			std::string dest_folder = args.m_dest_folder;
			std::cout << "dest_folder: " << dest_folder << std::endl;

			std::string fpath = make_path( dest_folder, str_path);
			std::cout << "fpath: " << fpath << std::endl;

// countermeasures against directory traversal
			if( std::string::npos == path.find( ".." ) )
			{
				// A nice path.

		if( existsFile(fpath)){
			std::cout << "exists: " << fpath << std::endl;
			return send_file(req, fpath, content_type);
	
		} else {
			std::string msg = 
			build_msg_not_found(str_path);
			std::cout << msg << std::endl;
			std::string msg_content_type("text/html");
			return send_not_found(req, msg,  msg_content_type);
		}

} else {
			// Bad path.
				return send_forbidden(req);
			}

		return restinio::request_accepted();
} );

	router->http_post( "/upload",
		[&]( const auto & req, const auto & )
		{
			std::string fname =
			save_file( args, req );
			std::cout << "fname: " << fname << std::endl;

			std::string text = 
			build_msg_uploaded(fname);
	std::cout << text << std::endl;

			std::string content_type("text/html");

			return send_text(req, text,  content_type);
		} );

	return router;
}


 /**
 *  run_server
 */
template < typename Server_Traits >
void run_server( const app_args_t & args )
{
std::cout << "listen port: " << args.m_port << std::endl;

	restinio::run(
		restinio::on_thread_pool< Server_Traits >( args.m_pool_size )
			.port( args.m_port )
			.address( args.m_address )
			.concurrent_accepts_count( args.m_pool_size )
			.request_handler( make_router( args ) ) );
}


/**
 * print_app_args
 */
void print_app_args( struct app_args_t args)
{
	std::cout << std::boolalpha << "help: " << args.m_help << std::endl;
std::cout << "dest_folder: " << args.m_dest_folder << std::endl;
	std::cout << "address: " << args.m_address << std::endl;
	std::cout << "port: " << args.m_port << std::endl;
	std::cout << "pool_size: " << args.m_pool_size << std::endl;
	std::cout << std::boolalpha << "trace_server: " << args.m_trace_server << std::endl;
}


 /**
 *  main
 */
int main( int argc, const char * argv[] )
{
	try
	{
		const auto args = app_args_t::parse( argc, argv );
		print_app_args(args);

		if( !args.m_help )
		{
			if( args.m_trace_server )
			{
				using traits_t =
					restinio::traits_t<
						restinio::asio_timer_manager_t,
						restinio::shared_ostream_logger_t,
						router_t >;

				run_server< traits_t >( args );
			}
			else
			{
				using traits_t =
					restinio::traits_t<
						restinio::asio_timer_manager_t,
						restinio::null_logger_t,
						router_t >;

				run_server< traits_t >( args );
			}
		}
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

