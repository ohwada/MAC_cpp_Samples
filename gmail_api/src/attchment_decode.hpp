 #pragma once
/**
   * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// parse_decode_AttchmentJsonFile_to_file

#include <fstream>
#include <string>
#include "attachment_json.hpp"
#include "response_msg_json.hpp"
#include "file_util.hpp"
#include "base64.hpp"


// prototype
bool parse_decode_AttchmentJsonFile_to_file(const std::string file_json, const std::string file_binary, std::string &ret_error);
bool writeFile(const std::string filepath, const std::string data, std::string &error);


/**
 *  parse_decode_AttchmentJsonFile_to_file
 */
bool parse_decode_AttchmentJsonFile_to_file(const std::string file_json, const std::string file_binary, std::string &ret_error)
{

    std::string data;
    int data_size;
    std::string error ;

    bool ret1 = readAttchmentJsonFile( file_json, 
data, &data_size, error ) ;

    if(!ret1){
            ret_error = error;
        return false;
    }

    std::string decoded = base64_decode(data);

    bool ret2 = writeFile(file_binary, decoded, error);

    if(!ret2){
        ret_error = error;
        return false;
    }

    return true;
}


/**
 * writeFile
 */
bool writeFile(const std::string filepath, const std::string data, std::string &error)
{

	std::ofstream file(filepath.c_str(), std::ios::binary | std::ios::out);
	if (!file){
        error = std::string("can not open: ") + filepath;
		return false;
    }

    int size = data.size();

    file.write( reinterpret_cast<char*>( (char *)data.c_str() ), sizeof(char) * size );

    file.flush();
    file.close();

    return true;
}
