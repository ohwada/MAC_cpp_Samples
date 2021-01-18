#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


#include <iostream>
#include "vmime/vmime.hpp"
#include "file_util.hpp"


// prototype
void printMessage(vmime::shared_ptr <vmime::message> msg );
bool saveMessage(  vmime::shared_ptr <vmime::message> msg );
bool saveMessageFile(  vmime::shared_ptr <vmime::message> msg, std::string filepath );
bool saveNetMessage( vmime::shared_ptr <vmime::net::message> net_msg );
bool saveNetMessageFile( vmime::shared_ptr <vmime::net::message> net_msg, std::string filepath );
void printNetMessage( vmime::shared_ptr <vmime::net::message> net_msg );


/**
 *  printMessage
 */
void printMessage(vmime::shared_ptr <vmime::message> msg )
{

	std::cout << std::endl;
	std::cout <<  msg->generate() << std::endl;
	std::cout << std::endl;

}


/**
 *   saveMessage
 */
bool saveMessage(  vmime::shared_ptr <vmime::message> msg )
{

    std::string filepath;
    getTimestampFileName("mail", "eml", filepath);

   bool ret = saveMessageFile( msg,  filepath );

    if(ret){
	    std::cout << "saved: " << filepath << std::endl;
    }

    return ret;

}


/**
 *   saveMessageFile
 */
bool saveMessageFile(  vmime::shared_ptr <vmime::message> msg, std::string filepath )
{

    std::ofstream ofs;
    ofs.open(filepath);

    if(!ofs.is_open()) {
        return false;
    }

    ofs << msg->generate();
    ofs.close();

    return true;

}


/** 
 *  saveNetMessage
  */      
bool saveNetMessage( vmime::shared_ptr <vmime::net::message> net_msg )
{
  
    std::string filepath;
    getTimestampFileName("mail", "eml", filepath);

    bool ret = saveNetMessageFile(net_msg, filepath );

    if(ret){
	    std::cout << "saved: " << filepath << std::endl;
    }   

    return ret;
}


/** 
 *  saveNetMessageFile
  */      
bool saveNetMessageFile( vmime::shared_ptr <vmime::net::message> net_msg, std::string filepath )
{
  
    std::ofstream ofs(filepath);
    if(!ofs){
        return false;
    }

	vmime::utility::outputStreamAdapter out(ofs);
	net_msg->extract(out);

    ofs.close();

    return true;
}


/** 
 *  printNetMessage
  */      
void printNetMessage( vmime::shared_ptr <vmime::net::message> net_msg )
{
	vmime::utility::outputStreamAdapter out(std::cout);
	net_msg->extract(out);

}
