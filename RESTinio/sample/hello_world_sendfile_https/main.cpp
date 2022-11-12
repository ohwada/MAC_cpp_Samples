/*
	Simple example using sendfile facility.
*/

#include <iostream>

#include <restinio/all.hpp>
#include <restinio/tls.hpp>

#include <fmt/format.h>

#include <clara.hpp>

//
// app_args_t
//
struct app_args_t
{
	bool m_help{ false };
	std::string m_address{ "localhost" };
	std::uint16_t m_port{ 8080 };
	std::size_t m_pool_size{ 1 };
	std::string m_certs_dir{ "." };
	std::string m_file;
	restinio::file_offset_t m_data_offset{ 0 };
	restinio::file_size_t m_data_size{ std::numeric_limits< restinio::file_size_t >::max() };
	std::string m_content_type{ "text/plain" };
	bool m_trace_server{ false };

	static app_args_t
	parse( int argc, const char * argv[] )
	{
		using namespace clara;

		app_args_t result;

		auto cli =
			Opt( result.m_address, "address" )
					["-a"]["--address"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING( "address to listen (default: {})" ),
							result.m_address ) )
			| Opt( result.m_port, "port" )
					["-p"]["--port"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING( "port to listen (default: {})" ),
							result.m_port ) )
			| Opt( result.m_pool_size, "thread-pool size" )
					[ "-n" ][ "--thread-pool-size" ]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"The size of a thread pool to run server (default: {})" ),
							result.m_pool_size ) )
			| Opt( result.m_certs_dir, "dir" )
					[ "--certs-dir" ]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"A directory with server.pem, key.pem, "
								"dh2048.pem (default: {})" ),
								result.m_certs_dir ) )
			| Opt( result.m_data_offset, "offset" )
					["-o"]["--data-offset"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"Offset of the data portion in file (default: {})" ),
								result.m_data_offset ) )
			| Opt( result.m_data_size, "size" )
					["-s"]["--data-size"]
					( "size of the data portion in file (default: to the end of file)" )
			| Opt( result.m_content_type, "content-type" )
					["--content-type"]
					( fmt::format(
							RESTINIO_FMT_FORMAT_STRING(
								"A value of 'Content-Type' header field (default: {})" ),
								result.m_content_type ) )
			| Opt( result.m_trace_server )
					[ "-t" ][ "--trace" ]
					( "Enable trace server" )
			| Arg( result.m_file, "file" ).required()
					( "Path to a file that will be served as response" )
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

template < typename Server_Traits >
void run_server( const app_args_t & args )
{
	// Since RESTinio supports both stand-alone ASIO and boost::ASIO
	// we specify an alias for a concrete asio namesace.
	// That's makes it possible to compile the code in both cases.
	// Typicaly only one of ASIO variants would be used,
	// and so only asio::* or only boost::asio::* would be applied.
	namespace asio_ns = restinio::asio_ns;

	asio_ns::ssl::context tls_context{ asio_ns::ssl::context::sslv23 };
	tls_context.set_options(
		asio_ns::ssl::context::default_workarounds
		| asio_ns::ssl::context::no_sslv2
		| asio_ns::ssl::context::single_dh_use );

	tls_context.use_certificate_chain_file( args.m_certs_dir + "/server.pem" );
	tls_context.use_private_key_file(
		args.m_certs_dir + "/key.pem",
		asio_ns::ssl::context::pem );
	tls_context.use_tmp_dh_file( args.m_certs_dir + "/dh2048.pem" );

	restinio::run(
		restinio::on_thread_pool< Server_Traits >( args.m_pool_size )
			.port( args.m_port )
			.address( args.m_address )
			.concurrent_accepts_count( args.m_pool_size )
			.tls_context( std::move( tls_context ) )
			.request_handler(
				[&]( auto req ){
					if( restinio::http_method_get() == req->header().method() &&
						req->header().request_target() == "/" )
					{
						try
						{
							auto sf = restinio::sendfile( args.m_file );
							sf.offset_and_size(
								args.m_data_offset,
								args.m_data_size );

							return
								req->create_response()
									.append_header(
										restinio::http_field::server,
										"RESTinio hello world server" )
									.append_header_date_field()
									.append_header(
										restinio::http_field::content_type,
										args.m_content_type )
									.set_body( std::move( sf ) )
									.done();
						}
						catch( const std::exception & )
						{
							return req->create_response( restinio::status_not_found() )
								.connection_close()
								.append_header_date_field()
								.done();
						}
					}

					return restinio::request_rejected();
			} ) );
}

int main( int argc, const char * argv[] )
{
	try
	{
		const auto args = app_args_t::parse( argc, argv );

		if( !args.m_help )
		{
			if( args.m_trace_server )
			{
				using traits_t =
					restinio::tls_traits_t<
						restinio::asio_timer_manager_t,
						restinio::shared_ostream_logger_t >;

				run_server< traits_t >( args );
			}
			else
			{
				run_server< restinio::default_tls_traits_t >( args );
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
