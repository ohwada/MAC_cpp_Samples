 #pragma once
/**
 * response_sender.hpp
 * 2022-06-01 K.OHWADA
 */

#include <restinio/all.hpp>

// prototype
restinio::request_handling_status_t send_file(const restinio::request_handle_t& req, std::string file_path, std::string content_type);
restinio::request_handling_status_t  send_text(const restinio::request_handle_t& req, std::string text,  std::string content_type);
restinio::request_handling_status_t send_not_found(restinio::request_handle_t& req, std::string body,  std::string content_type);
restinio::request_handling_status_t  send_forbidden(restinio::request_handle_t& req);


const std::string SERVER_NAME(
"RESTinio Server");



/**
 * send_file
 */
restinio::request_handling_status_t send_file(
const restinio::request_handle_t& req, std::string file_path, std::string content_type)
{

	try
	{
			auto sf = restinio::sendfile( file_path );
			sf.offset_and_size(0);

			auto resp = req->create_response();
			resp.append_header( restinio::http_field::server,  SERVER_NAME );
			resp.append_header_date_field();
			resp.append_header(
			restinio::http_field::content_type,
			content_type );
			resp.set_body( std::move( sf ) );

				return resp.done();
	}
		catch( const std::exception e )
	{
		std::cerr << e.what() << std::endl;
	}
	return restinio::request_accepted();
}


/**
 * send_text
 */
restinio::request_handling_status_t  send_text(
const restinio::request_handle_t& req, std::string text,  std::string content_type)
{
		auto resp = req->create_response();
		resp.append_header( "Server",  SERVER_NAME );
		resp.append_header_date_field();
		resp.append_header(
			restinio::http_field::content_type, content_type );
			resp.set_body( text );

		return resp.done();
}


/**
 * send_not_found
 */
restinio::request_handling_status_t  send_not_found(restinio::request_handle_t& req, std::string body,  std::string content_type)
{
	auto resp = 
    req->create_response( restinio::status_not_found() );

	resp.append_header_date_field();
	resp.append_header( restinio::http_field::content_type, content_type );
	resp.set_body(body);
	resp.connection_close();

	return resp.done();
}

/**
 * send_forbidden
 */
restinio::request_handling_status_t  send_forbidden(restinio::request_handle_t& req)
{
		auto resp =
		req->create_response( restinio::status_forbidden() );
		resp.append_header_date_field();
		resp.connection_close();

		return resp.done();
}
