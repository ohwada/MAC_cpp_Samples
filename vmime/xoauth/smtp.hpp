#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// common function for SMTP client
// original : https://github.com/kisli/vmime/blob/master/examples/example6.cpp


//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002 Vincent Richard <vincent@vmime.org>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Linking this library statically or dynamically with other modules is making
// a combined work based on this library.  Thus, the terms and conditions of
// the GNU General Public License cover the whole combination.
//


#include <iostream>
#include <sstream>
#include<fstream>
#include <vector>
#include <map>
#include <locale>
#include <clocale>
#include <string>

#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"

#include "tracer.hpp"
#include "authenticator.hpp"
#include "timeoutHandler.hpp"

#include "exception _helper.hpp"
#include "smtp_msg_build.hpp"
#include "mail_json.hpp"
#include "file_util.hpp"


// prototype
vmime::shared_ptr <vmime::message> buildMessage( std::string subject, std::string mail_from, std::string mail_to ) ;
bool sendMessage( 
vmime::shared_ptr <vmime::net::session> session, std::string smtp_url,  
std::string user, std::string passwd, 
vmime::shared_ptr <vmime::message> msg, 
vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, 
bool verbose );
bool sendMsgSecure( 
vmime::shared_ptr<vmime::net::transport> tr,  
vmime::shared_ptr <vmime::message> msg,
vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv,
bool verbose );
void printMessage(vmime::shared_ptr <vmime::message> msg );
void saveMessage(  vmime::shared_ptr <vmime::message> msg );





/**
 *  sendMessage
 */
bool sendMessage( 
vmime::shared_ptr <vmime::net::session> session, std::string smtp_url,  
std::string user, std::string passwd, 
vmime::shared_ptr <vmime::message> msg, 
vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv,
bool verbose )
{

    if(verbose){
        std::cout << "url: " << smtp_url << std::endl;
        std::cout << "user: " << user << std::endl;
        std::cout << "password: " << passwd << std::endl;
    }

    vmime ::utility::url url( smtp_url );

    vmime::shared_ptr <vmime::net::transport> tr;	
	if ( !user.empty() && !passwd.empty() ) {
			tr = session->getTransport(url);
            tr-> setProperty("auth.username", user);
            tr-> setProperty( "auth.password", passwd);

    } else {
			tr = session->getTransport(url, vmime::make_shared <interactiveAuthenticator>());
        std::cout << "interactiveAuthenticator "  << std::endl;
	}

    tr-> setProperty( "options.need-authentication", true);

    return sendMsgSecure(  tr, msg, cv,  verbose ) ;

}


/**
 *  sendMsgSecure
 */
bool sendMsgSecure( 
vmime::shared_ptr<vmime::net::transport> tr,  
vmime::shared_ptr <vmime::message> msg,
vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, bool verbose )
{

	try {

#if VMIME_HAVE_TLS_SUPPORT

		// Enable TLS support if available
		tr->setProperty("connection.tls", true);

		// Set the time out handler
		tr->setTimeoutHandlerFactory(vmime::make_shared <timeoutHandlerFactory>());

		// Set the object responsible for verifying certificates, in the
		// case a secured connection is used (TLS/SSL)
		tr->setCertificateVerifier( cv );

#endif // VMIME_HAVE_TLS_SUPPORT


		// Trace communication between client and server
		vmime::shared_ptr <std::ostringstream> traceStream = vmime::make_shared <std::ostringstream>();
		tr->setTracerFactory(vmime::make_shared <myTracerFactory>(traceStream));

		// Connect to server
		tr->connect();

		// Send the message		
		tr->send(msg);
   
		// Display connection log
        if (verbose) {
		    std::cout << std::endl;
		    std::cout << "Connection Trace:" << std::endl;
		    std::cout << "=================" << std::endl;
		    std::cout << traceStream->str();
        }

		tr->disconnect();

	} catch (vmime::exception& e) {

		std::cerr << std::endl;
		std::cerr << e << std::endl;
		return false;

	} catch (std::exception& e) {

		std::cerr << std::endl;
		std::cerr << "std::exception: " << e.what() << std::endl;
		return false;
	}

    return true;
}


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
void saveMessage(  vmime::shared_ptr <vmime::message> msg )
{

    std::string file;
    getTimestampFileName("mail", "eml", file);

    std::ofstream ofs(file);
    ofs << msg->generate();
    ofs.close();

	std::cout << "saved: " << file << std::endl;
}

