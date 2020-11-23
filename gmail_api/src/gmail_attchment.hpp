 #pragma once
/**
   * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// downloadAttachment

#include <fstream>
#include <string>
#include "gmail_api_request.hpp"
#include "attchment_decode.hpp"


// prototype
bool downloadAttachment(  std::string access_token, std::string msg_id, struct MailPart part, bool is_verbose );

/**
 * downloadAttachment
 */
bool downloadAttachment(  std::string access_token, std::string msg_id, struct MailPart part, bool is_verbose )
{

    const std::string LF = "\n";

    std::string timestamp;
    getTimestamp(timestamp);

   std::string fname  = std::string("attach_") + timestamp;
    std::string file_json = fname + std::string(".json");
    std::string file_text = fname + std::string(".txt");

    std::string mimeType = part.mimeType;
    std::string filename = part.filename;
    std::string attachmentId = part.attachmentId;

    std::string info = 
    std::string("messageId: ") + msg_id + LF
    + std::string("attachmentId: ") + attachmentId + LF
    + std::string("filename: ") + filename + LF
   + std::string( "mimeType: ") + mimeType + LF;

    bool ret1 = writeTextFile(file_text, info);

    if(ret1){
        if(is_verbose) {
            std::cout <<  "saved: " << file_text << std::endl;
        }
    } else {
        if(is_verbose) {
            std::cout << "writeTextFile faild: " << file_text << std::endl;
        }
    }

    std::string error;

    bool ret2 = api_attachment_request_to_file( msg_id, attachmentId,  access_token, file_json, error,  is_verbose);

    if(ret2){
        if(is_verbose) {
            std::cout << "saved: " << file_json << std::endl;
        }
    } else {
        std::cout << "api_attachment_request_to_file: "  << error << std::endl;
        return false;
    }




    bool ret3 = parse_decode_AttchmentJsonFile_to_file( file_json, filename, error);

    if(ret3){
        if(is_verbose) {
            std::cout << "saved: " << filename << std::endl;
        }
    } else {
       std::cout << "parse_decode_AttchmentJsonFile_to_file: " << error << std::endl;
        return false;
    }

    return true;
}

