#pragma once
/**
 * timestamp.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Path.h"
#include "Poco/Format.h"


// prototype
std::string build_timestamp_file_path(  std::string dir,  std::string prefix, std::string ext);
std::string get_timestamp_file_name(std::string prefix, std::string ext);
std::string get_timestamp();
std::string make_path(std::string dir, std::string fname);


/**
 * build_timestamp_file_path
 */
std::string build_timestamp_file_path(  std::string dir,  std::string prefix, std::string ext)
{
    std::string fname = get_timestamp_file_name(prefix, ext);

    return make_path(dir, fname);
}


/** 
 *  get_timestamp_file_name
  */ 
std::string get_timestamp_file_name(std::string prefix, std::string ext)
{
    const std::string FORMAT("%s_%s.%s");

    std::string timestamp = get_timestamp();

    std::string fname;
    Poco::format(fname, FORMAT,  prefix, timestamp, ext);

    return fname;
}


/**
 *  get_timestamp
 */
std::string get_timestamp()
{

// %F - fractional seconds(microseconds) 
// it will be overwritten by favicon.ico
// if it is in seconds unit
    const std::string FORMAT("%Y%m%d%H%M%S-%F");

	Poco::LocalDateTime now;
	return Poco::DateTimeFormatter::format(now, FORMAT);

}


/**
 * make_path
 */
std::string make_path(std::string dir, std::string fname)
{
   Poco::Path parent(dir);
    Poco::Path path(parent, fname);
    return path.toString();
}