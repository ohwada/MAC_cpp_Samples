#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// recievw mail from pop3 (or imap) server with SSL 

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
#include <string>
#include <vector>

#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"

#include "plugin_tracer.hpp"
#include "plugin_authenticator.hpp"
#include "plugin_timeoutHandler.hpp"
#include "plugin_exception _helper.hpp"
#include "vmime_folder.hpp"
#include "vmime_net_message.hpp"
#include "json_mail.hpp"


/** 
 * typedef
  */
typedef std::map <vmime::size_t, vmime::shared_ptr <vmime::net::message> >  NetMessageList;


// prototype
bool connectServer( int mode, vmime::shared_ptr <vmime::net::session> session, std::string pop3_url, std::string imap_url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) ;
bool connectPop3( vmime::shared_ptr <vmime::net::session> session, std::string url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) ;
bool connectImap( vmime::shared_ptr <vmime::net::session> session, std::string url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) ;
bool connectStore( int mode, vmime::shared_ptr <vmime::net::session> session, std::string pop3_url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose) ;
void procFolder(	 int mode, vmime::shared_ptr <vmime::net::store> st, vmime::shared_ptr <std::ostringstream> traceStream, int limit, bool verbose );
std::vector <std::string> buildActionMenu();
void showTrace( vmime::shared_ptr <std::ostringstream> traceStream );
void pop3_showFlags(int mode, vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> net_msg );
void pop3_addMessage(int mode, vmime::shared_ptr <vmime::net::folder> f);
void pop3_copyMessage(int mode, vmime::shared_ptr <vmime::net::folder> f,
	vmime::shared_ptr <vmime::net::message> net_msg);
vmime::shared_ptr <vmime::net::folder> pop3_changeFolder(int mode,  vmime::shared_ptr <vmime::net::store> st );
void pop3_showStructure(int mode, vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> net_msg);
int getModeFromCommandLine(int argc, char* argv[]);
int getLimitFromCommandLine(int argc, char* argv[]);


// global constant
const int MODE_POP3 = 0;
const int MODE_IMAP = 1;


/** 
 * connectServer
  */
bool connectServer( int mode, vmime::shared_ptr <vmime::net::session> session, std::string pop3_url, std::string imap_url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) 
{
    bool ret = false;
    if(mode == MODE_POP3){
	        ret = connectPop3( session, pop3_url, user, passwd, cv, limit, verbose );
    } else if (mode == MODE_IMAP){
	        ret = connectImap( session, imap_url, user, passwd, cv, limit, verbose );
    }
    return ret;
}


/** 
 * connectPop3
  */
bool connectPop3( vmime::shared_ptr <vmime::net::session> session, std::string url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) 
{
    return connectStore( MODE_POP3, session, url, user, passwd, cv, limit, verbose ); 
}


/** 
 * connectImap
  */
bool connectImap( vmime::shared_ptr <vmime::net::session> session, std::string url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) 
{
    return connectStore( MODE_IMAP, session, url, user, passwd, cv, limit, verbose ); 
}


/** 
 * Connect to a message store interactively.
  */
bool connectStore( int mode, vmime::shared_ptr <vmime::net::session> session, std::string str_url, std::string user, std::string passwd, vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv, int limit, bool verbose ) 
{

    bool is_exception = false;


    if(verbose){
        std::cout << "url: " << str_url << std::endl;
        std::cout << "user: " << user << std::endl;
        std::cout << "password: " << passwd << std::endl;
    }


	vmime::utility::url url(str_url);
 	url.setUsername (user); 
	url.setPassword (passwd);

	try {

		// If no authenticator is given in argument to getStore(), a default one
		// is used. Its behaviour is to get the user credentials from the
		// session properties "auth.username" and "auth.password".
		vmime::shared_ptr <vmime::net::store> st;

		if (url.getUsername().empty() || url.getPassword().empty()) {
			st = session->getStore(url, vmime::make_shared <interactiveAuthenticator>());
		} else {
			st = session->getStore(url);
		}

#if VMIME_HAVE_TLS_SUPPORT

		// Enable TLS support if available
		//st->setProperty("connection.tls", true);

		// Set the time out handler
		st->setTimeoutHandlerFactory(vmime::make_shared <timeoutHandlerFactory>());

		// Set the object responsible for verifying certificates, in the
		// case a secured connection is used (TLS/SSL)
		st->setCertificateVerifier( cv );

#endif // VMIME_HAVE_TLS_SUPPORT

		// Trace communication between client and server
		vmime::shared_ptr <std::ostringstream> traceStream = vmime::make_shared <std::ostringstream>();
		st->setTracerFactory(vmime::make_shared <myTracerFactory>(traceStream));

		// Connect to the mail store
		st->connect();

		// Display some information about the connection
		vmime::shared_ptr <vmime::net::connectionInfos> ci = st->getConnectionInfos();

        if (verbose) {
		    std::cout << std::endl;
		    std::cout << "Connected to '" << ci->getHost() << "' (port " << ci->getPort() << ")" << std::endl;
		    std::cout << "Connection is " << (st->isSecuredConnection() ? "" : "NOT ") << "secured." << std::endl;
        }

		// Display connection log
        if (verbose) {
		    std::cout << std::endl;
		    std::cout << "Connection Trace:" << std::endl;
		    std::cout << "=================" << std::endl;
		    std::cout << traceStream->str();
        }

		procFolder( mode, st, traceStream, limit, verbose );

		st->disconnect();

	} catch (vmime::exception& e) {
        is_exception = true;
		std::cerr << std::endl;
		std::cerr << e << std::endl;

	} catch (std::exception& e) {
        is_exception = true;
		std::cerr << std::endl;
		std::cerr << "std::exception: " << e.what() << std::endl;
	}

    return !is_exception ;
}


/**
 * procFolder
 */
void procFolder( int mode, vmime::shared_ptr <vmime::net::store> st, vmime::shared_ptr <std::ostringstream> traceStream,  int limit, bool verbose )
{

    const int START_MIN = 1;

	// Open the default folder in this store
		vmime::shared_ptr <vmime::net::folder> f = st->getDefaultFolder();

		f->open(vmime::net::folder::MODE_READ_WRITE);

		vmime::size_t net_msg_count  = f->getMessageCount();

		std::cout << std::endl;
		std::cout << net_msg_count << " message(s) in your inbox" << std::endl;

    int start = net_msg_count - limit + 1;
    if(start <  START_MIN){
        start =  START_MIN;
    }

 	std::cout << "get latest " << limit << " messages " << std::endl;

	vmime::shared_ptr <vmime::net::message> net_msg;

    vmime::shared_ptr< vmime::message > msg;

    vmime::shared_ptr <vmime::header> header;

	 NetMessageList  netMsgList;

	std::vector< vmime::shared_ptr< vmime::message > > msg_list;

	std::vector< struct HeaderInfo > headerInfos;

	std::vector<std::string> headerMenu;

    struct HeaderInfo header_info;

	for(int i=start; i<=net_msg_count; i++) {

		net_msg = f->getMessage(i);
		if(!net_msg){
			std::cout << "getMessage failed: " << i << std::endl;
			continue;
		}



// progress
        if(verbose){
    	    fprintf(stderr, "\r fetch [ %2d / %2lu ]", i, net_msg_count);
        }

		f->fetchMessage(net_msg, vmime::net::fetchAttributes::FULL_HEADER);

		 netMsgList.insert( NetMessageList::value_type(i, net_msg));

        msg = net_msg->getParsedMessage();
        msg_list.push_back(msg);

        header = msg->getHeader();

        getHeaderInfo( header, header_info );
        header_info.msg_number = i;
		headerInfos.push_back( header_info );
		headerMenu.push_back( header_info.label );

	} // for

    if(verbose){
        fprintf(stderr, "\n"); // line feed
    }

    int empty = 0;

    vmime::shared_ptr< vmime::message > current_msg;

	while(1)
	{

        int menu_num = printMenu(headerMenu, empty);
		if (menu_num == 0) {
		        f->close(true);  // 'true' to expunge deleted messages
				std::cout << "goodby" << std::endl;
				return;
		} else {
				bool ret = checkNumber(menu_num, 0, net_msg_count);
				if(!ret){
					hitEnterKey();
					continue;
				}
		}

        int net_msg_num = 0; 

        size_t msg_list_size  = msg_list.size();

        struct HeaderInfo current_info;

        int index = menu_num -1;

        if( (index >= 0)&&(index < msg_list.size() )) {
            current_msg = msg_list[index];
            current_info = headerInfos[index];
        } else {
		    std::cout << "out of range: " << menu_num 
            << "size: " <<  msg_list_size  << std::endl;
        }

       int msg_number = current_info.msg_number;

		 NetMessageList::iterator it =  netMsgList.find(msg_number);
		if (it !=  netMsgList.end()) {
				net_msg = (*it).second;
	    }

// print header
	     std::cout << "Subject: " << current_info.subject << std::endl;
	     std::cout << "From: " << current_info.from << std::endl;
	     std::cout << "Date: " << current_info.date << std::endl;

    printTextBody( current_msg );

// get attachments
    std::vector <vmime::shared_ptr <const vmime::attachment> > attchs = getAttachments( current_msg );

    size_t attchs_size = attchs.size();
    if(attchs_size > 0){
        std::cout <<std::endl;
        std::cout << "this message has " << attchs_size << " attachment(s)" << std::endl;
    }



std::vector<std::string> actionMenuList = buildActionMenu();
int action_menu_size = actionMenuList.size();
vmime::shared_ptr <vmime::net::folder> new_folder;

while(1)
{
        int choice = printMenu( actionMenuList, empty);
        bool ret3= checkNumber(choice, 0, action_menu_size);
        if(!ret3){
            continue;
        }

        if(choice == 0){
            break;
        }

			switch (choice) 
            {

				// Show message flags
				case 1:
                    pop3_showFlags( mode, f, net_msg );
                    break;

				// Show message structure
				case 2:
                    pop3_showStructure(mode, f, net_msg);
					break;

				// Show message header
				case 3:
                    showHeader(f, net_msg);
					break;

				// Show message envelope
				case 4: 
                    showEnvelope( f, net_msg);
					break;
				
				// Extract whole message
				case 5: 
                        extractNetMessage(net_msg);
					    break;

				// Extract attachments
				case 6: 
                       extractNetAttachments(net_msg);
                        break;
				
				// Status
				case 7: 
                    showStatus(f);
					break;
				
				// List folders
				case 8: 
                    showFolders(st);
					break;
				
				// Change folder
				case 9: 
                    new_folder = pop3_changeFolder(mode,  st);
                        if(new_folder != NULL){
		                    f->close(true);  // 'true' to expunge deleted messages
                            f = new_folder;
                        }
					break;

				// Add message
				case 10: 
                        pop3_addMessage(mode, f);
                        break;

				// Copy message
				case 11:  
                    pop3_copyMessage( mode,  f, net_msg);
					break;
			
			// Display trace output
				case 12:
                    showTrace( traceStream );
                    break;

		// Display body
				case 13:
                    showBody( current_msg );
                    break;

		// Save nessage
				case 14:
                        saveNetMessage( net_msg );
                    break;

    } // switch

	hitEnterKey();

} // while action

			hitEnterKey();

	} // while message

}


/**
 *  buildActionMenu
 */
std::vector <std::string> buildActionMenu()
{

    std::vector <std::string> choices;

    choices.push_back("Show message flags");
    choices.push_back("Show message structure");
	choices.push_back("Show message header");
	choices.push_back("Show message envelope");
	choices.push_back("Extract whole message");
	choices.push_back("Extract attachments");
	choices.push_back("Status");
	choices.push_back("List folders");
	choices.push_back("Change folder");
	choices.push_back("Add message (to the current folder)");
	choices.push_back("Copy message (into the current folder)");
	choices.push_back("Display trace output");

	choices.push_back("Show body");
	choices.push_back("Save message");

	return choices;
}





/**
 *  pop3_addMessage
  */
void pop3_addMessage(int mode, vmime::shared_ptr <vmime::net::folder> f)
{

    std::cout << "add message" << std::endl;
    if(mode == MODE_POP3){
        std::cout << "pop3 not suport, try imap" << std::endl;
        return;
    }

    addMessage(f);

}


/**
 *  pop3_copyMessage
  */
void pop3_copyMessage(int mode, vmime::shared_ptr <vmime::net::folder> f,
	vmime::shared_ptr <vmime::net::message> net_msg)
{

    std::cout << "copy message" << std::endl;
    if(mode == MODE_POP3){
        std::cout << "pop3 not suport, try imap" << std::endl;
        return;
    }

    copyMessage(f, net_msg);

}


/**
 *  pop3_changeFolder
  */
vmime::shared_ptr <vmime::net::folder> pop3_changeFolder(int mode,  vmime::shared_ptr <vmime::net::store> st )
{

    std::cout << "change folder" << std::endl;
    if(mode == MODE_POP3){
        std::cout << "pop3 not suport, try imap" << std::endl;
        return NULL;
    }

    return changeFolder( st );

}


/**
 *  pop3_showStructure
  */
void pop3_showStructure(int mode, vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> net_msg)
{
    std::cout << "show message structure" << std::endl;
    if(mode == MODE_POP3){
        std::cout << "pop3 not suport, try imap" << std::endl;
        return;
    }

    showStructure(f, net_msg);

}


/**
 *   showTrace
 */
void showTrace( vmime::shared_ptr <std::ostringstream> traceStream )
{
    std::cout << std::endl;
	std::cout << "Connection Trace:" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << traceStream->str();
}



/**
 *  pop3_showFlags
 */
void pop3_showFlags(int mode, vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> net_msg )
{
    std::cout << "show message flags" << std::endl;
    if(mode == MODE_POP3){
        std::cout << "pop3 not suport, try imap" << std::endl;
        return;
    }

    showFlags(f, net_msg );

}



/**
 *  getModeFromCommandLine
 */
int getModeFromCommandLine(int argc, char* argv[])
{

    int mode = MODE_POP3;

    if(argc == 2) {
        mode = atoi(argv[1] );
    } else {
        std::cout << "Usage: " << argv[0] << " [mode] [limit] "  << std::endl;
    }

    switch(mode)
    {
    case MODE_POP3:
        std::cout << "mode: pop3" << std::endl;
        break;
    case MODE_IMAP:
        std::cout << "mode: imap" << std::endl;
        break;
    default:
        std::cout << "mode must be 0 or 1" << std::endl;
        mode = -1;
    }

    return mode;
}


/**
 *  getLimitFromCommandLine
 */
int getLimitFromCommandLine(int argc, char* argv[])
{
    int limit = 10;

    if(argc == 3) {
        limit = atoi(argv[2] );
    }

    return limit;
}