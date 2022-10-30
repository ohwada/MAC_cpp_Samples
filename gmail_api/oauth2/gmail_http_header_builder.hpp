#pragma once
/**
 * http_header_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "Poco/Format.h"

// prototype
std::string build_header_authorization(std::string access_token);


/**
 * build_header_authorization
 */
std::string build_header_authorization(std::string access_token)
{
	const std::string FORMAT_AUTHORIZATION( 
	"Authorization: Bearer %s");

	std::string header;
	Poco::format(header, FORMAT_AUTHORIZATION, access_token );

    return header;
}


