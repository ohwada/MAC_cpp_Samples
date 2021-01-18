#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// fuctionn for file

#include <fstream>
#include "vmime/vmime.hpp"
#include "file_util.hpp"

// prototype
 vmime::shared_ptr <vmime::message>
readMailFile(std::string filepath, std::string &error);


/**
 *  readMailFile
 */
 vmime::shared_ptr <vmime::message>
readMailFile( std::string filepath, std::string &error )
{

    if( !existsFile(filepath ) ) {
        error = "not found: " + filepath;
        return vmime::null;
    }
	
    vmime::shared_ptr <vmime::message> msg = vmime::make_shared<vmime::message>();

    vmime::string data;

    std::ifstream file;
    file.open( filepath, std::ios::in | std::ios::binary);

    if( !file.is_open() ){
        error = "can not open: " + filepath;
        return vmime::null;
    }

    vmime::utility::inputStreamAdapter is(file);
    vmime::utility::outputStreamStringAdapter os(data);
    vmime::utility::bufferedStreamCopy(is , os);

    msg->parse(data);

    file.close();

    return msg;
}
