#pragma once
/**
 * libcurl Sample
 * 2020-07-01 K.OHWADA
 */


// readGmailJsonFile

#include <iostream>
#include <fstream>
#include <string>
#include "json/json.h"


/**
 * struct MailParam
 */
struct MailParam {
std::string smtp_url;
std::string pop_url;
std::string imap_url;
std::string user;
std::string passwd;
std::string to;
std::string from;
};


// prototype
bool readMailJsonFile( std::string filepath, MailParam *param, std::string &error ) ;



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

    Json::Value jv_pop_url = root.get("pop_url",  Json::nullValue );
   if(jv_pop_url.isNull() ){
        error += "\n not found pop_url \n";
    } else {
        p.pop_url = jv_pop_url.asString();
    }

    Json::Value jv_imap_url = root.get("imap_url",  Json::nullValue );
   if(jv_imap_url.isNull() ){
        error += "\n not found imap_url \n";
    } else {
        p.imap_url = jv_imap_url.asString();
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
    std::cout << "pop_url: " << p.pop_url << std::endl;
    std::cout << "imap_url: " << p.imap_url << std::endl;
    std::cout << "user: " << p.user << std::endl;
    std::cout << "passwd: " << p.passwd << std::endl;
    std::cout << "to: " << p.to << std::endl;
    std::cout << "from: " << p.from << std::endl;
}

