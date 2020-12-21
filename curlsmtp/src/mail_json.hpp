#pragma once
/**
 * curlsmtp sample
 * 2020-07-01 K.OHWADA
 */


// readGmailJsonFile

#include <fstream>
#include <string>
#include "json/json.h"
#include "mail_directory.h"


/**
 * struct MailParam
 */
struct MailParam {
std::string smtp_url;
std::string smtp_server;
int smtp_port;
std::string user;
std::string passwd;
std::string to;
std::string from;
};


// prototype
MailParam  getGmailParam(void);
 MailParam  getUbuntuMailParam(void);
bool readMailJsonFile( std::string filepath, MailParam *param, std::string &error ) ;
void printMailParam( MailParam p );



/**
 * getGmailParam
 */
 MailParam  getGmailParam(void) 
{

    MailParam p;
    std::string error;

    std::string filepath = getMailDir() + std::string( "/gmail.json" );

    bool ret = readMailJsonFile(filepath, &p, error ); 
    if(!ret){
        std::cout << error << std::endl;
    }

    return p;
}


/**
 * getUbuntuMailParam
 */
 MailParam  getUbuntuMailParam(void) 
{

    MailParam p;
    std::string error;

   std::string filepath = getMailDir() + std::string( "/ubuntu.json" );

    bool ret = readMailJsonFile(filepath, &p, error ); 
    if(!ret){
        std::cout << error << std::endl;
    }

    return p;
}


/**
 * readMailJsonFile
 */
bool readMailJsonFile( std::string filepath, MailParam *param, std::string &error ) 
{

    MailParam p;

    Json::Value root;
   std:: ifstream ifs;

    ifs.open(filepath);
    if(!ifs){
        error = "can not open: " + filepath;
        return false;
    }

    Json::CharReaderBuilder builder;
    // builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        error = errs;
        return false;
  }


    Json::Value jv_smtp_url = root.get("smtp_url",  Json::nullValue );
   if(jv_smtp_url.isNull() ){
        error += "\n not found smtp_url \n";
    } else {
        p.smtp_url = jv_smtp_url.asString();
    }

    Json::Value jv_smtp_server = root.get("smtp_server",  Json::nullValue );
   if(jv_smtp_server.isNull() ){
        error += "\n not found smtp_server \n";
    } else {
        p.smtp_server = jv_smtp_server.asString();
    }

    Json::Value jv_smtp_port = root.get("smtp_port",  Json::nullValue );
   if(jv_smtp_port.isNull() ){
        error += "\n not found smtp_port \n";
    } else {
        p.smtp_port = jv_smtp_port.asInt();
    }


    Json::Value jv_user = root.get("user",  Json::nullValue );
   if(jv_user.isNull() ){
        error += "not found user \n";
    } else {
        p.user = jv_user.asString();
    }

    Json::Value jv_passwd = root.get("passwd",  Json::nullValue );
   if(jv_passwd.isNull() ){
        error += "not found passwd \n";
    } else {
        p.passwd = jv_passwd.asString();
    }


    Json::Value jv_to = root.get("to",  Json::nullValue );
   if(jv_to.isNull() ){
        error += "not found to \n";
    } else {
        p.to = jv_to.asString();
    }


    Json::Value jv_from = root.get("from",  Json::nullValue );
   if(jv_from.isNull() ){
        error += "not found from \n";
    } else {
        p.from = jv_from.asString();
    }

    *param = p;
    return true;
}


/**
 *  printMailParam
 */
void printMailParam( MailParam p )
{
    std::cout << "smtp_url: " << p.smtp_url << std::endl;
    std::cout << "smtp_server: " << p.smtp_server << std::endl;
    std::cout << "smtp_port: " << p.smtp_port << std::endl;
    std::cout << "user: " << p.user << std::endl;
    std::cout << "passwd: " << p.passwd << std::endl;
    std::cout << "to: " << p.to << std::endl;
    std::cout << "from: " << p.from << std::endl;
}

