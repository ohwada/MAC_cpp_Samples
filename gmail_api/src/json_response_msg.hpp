#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// readMessageResponseJsonFile

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json/json.h"


/**
 * struct MailPart
 */
struct MailPart
{
std::string partId;
std::string mimeType;
std::string filename;
int size;
std::string data;
std::string attachmentId;
};


/**
 * struct MailMessage
 */
struct MailMessage
{
std::string id;
std::string subject;
std::string from;
std::string date;
std::string content_type;
std::string content_transfer; 
std::string  snippet;
std::vector<struct MailPart> parts;
};


// prototype
 bool parseMessageResponseJson( std::string json, 
struct MailMessage &msg,
std::string &error, bool is_verbose) ;
void printMailMessage(struct MailMessage msg);
void printMailPart( struct MailPart part);


/**
 * parseMessageResponseJson
 */
bool parseMessageResponseJson( std::string json, 
struct MailMessage &msg,
std::string &error, bool is_verbose) 
{

    Json::Value root;
    JSONCPP_STRING err;

    const auto  length = 
    static_cast<int>( json.length());

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

char const * 	begin = json.c_str();
char const * 	end = json.c_str() +  length;

    if (!reader->parse( begin,  end, &root,
                       &err)) {
        error = err;
        return false;
    }

 
    msg.id = root["id"].asString();
    msg.snippet = root["snippet"].asString();


    Json::Value payload = root["payload"];
    if( payload.isNull() ){
        error = "not found payload";
        return false;
    }


    Json::Value headers = payload["headers"];
    if( headers.isNull() ){
        error = "not found headers";
        return false;
    }

    for ( int index = 0; index < headers.size(); ++index ){
        Json::Value header = headers[index];
        std::string name = header["name"].asString();
        std::string value = header["value"].asString();
        if( name == "Subject") {
            msg.subject = value;
        }
        if( name == "From") {
            msg.from = value;
        }
        if( name == "Date") {
            msg.date = value;
        }
        if( name == "Content-Type") {
            msg.content_type = value;
        }
        if( name == "Content-Transfer-Encoding") {
            msg.content_transfer = value;
        }
        if(is_verbose){
            std::cout << name << " ; " << value << std::endl;
        }
    } // for

    Json::Value parts = payload["parts"];
    if( parts.isNull() ){
        return true;
    }

    for ( int index = 0; index < parts.size(); ++index ){
        Json::Value part = parts[index];

         std::string partId;
        std::string mimeType;
        std::string filename;
        int body_size;
        std::string body_data;
        std::string attachmentId;

        Json::Value jv_partId = part["partId"];
        if( !jv_partId.isNull() ){
            partId = jv_partId.asString();
        }

        Json::Value jv_mimeType = part["mimeType"];
        if( !jv_partId.isNull() ){
            mimeType = jv_mimeType.asString();
        }

        Json::Value jv_filename = part["filename"];
        if( !jv_filename.isNull() ){
            filename = jv_filename.asString();
        }


        Json::Value body = part["body"];
        if( ! body.isNull() ){

                Json::Value jv_size = body["size"];
                if( !jv_size.isNull() ){
                        body_size = jv_size.asInt();
                }

                Json::Value jv_data = body["data"];
                if( !jv_data.isNull() ){
                        body_data = jv_data.asString();
                }

                Json::Value jv_attachmentId = body["attachmentId"];
                if( !jv_attachmentId.isNull() ){
                        attachmentId = jv_attachmentId.asString();
                }
        }

        struct MailPart mailPart;
        mailPart.partId = partId;
        mailPart.mimeType = mimeType;
        mailPart.filename = filename;
        mailPart.size = body_size;
        mailPart.data = body_data;
        mailPart.attachmentId = attachmentId;
        msg.parts.push_back(mailPart);

    } // for


    return true;
}



/**
 * printMailMessage
 */
void printMailMessage(struct MailMessage msg)
{

    std::string id = msg.id;
    std::string subject = msg.subject;
    std::string from = msg.from;
    std::string date = msg.date;
    std::string content_type = msg.content_type;
    std::string content_transfer = msg.content_transfer;
    std::string snippet = msg.snippet;

    std::cout << std::endl;
    std::cout << "id: " << id << std::endl;
    std::cout << "Subject: " << subject << std::endl;
    std::cout << "From: " << from << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Content-Type: " << content_type << std::endl;
    std::cout << "Content-Transfer: " << content_transfer << std::endl;

    if( snippet.length() > 0 ) {
    std::cout << std::endl;
        std::cout << "----------"  << std::endl;
        std::cout << snippet << std::endl;
        std::cout << "----------"  << std::endl;
    } else {
        std::cout << "snippet: " << snippet << std::endl;
    }

}


/**
 * printMailPart
 */
void printMailPart( struct MailPart part)
{
    std::string partId = part.partId;
    std::string mimeType = part.mimeType;
    std::string filename = part.filename;
    int size = part.size;
    std::string data = part.data;
    std::string attachmentId = part.attachmentId;

    std::cout << "partId: " << partId << std::endl;
    std::cout << "mimeType: " << mimeType << std::endl;
    std::cout << "filename: " << filename << std::endl;
    std::cout << "size: " << size << std::endl;
    std::cout << "data: " << data << std::endl;
    std::cout << "attachmentId: " << attachmentId << std::endl;
}
