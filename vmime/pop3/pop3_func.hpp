/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// common function for pop3

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
#include <fstream>
#include <vector>
#include <map>
#include <locale>
#include <clocale>
#include <string>
#include <regex> 
#include <stdio.h>


#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"

#include "tracer.hpp"
#include "authenticator.hpp"
#include "timeoutHandler.hpp"
#include "exception _helper.hpp"

#include "vmime_header.hpp"
#include "vmime_body.hpp"
#include "file_util.hpp"


/**
 * typedef 
 */
typedef std::map <vmime::size_t, vmime::shared_ptr <vmime::net::message> > MessageList;


// prototype
bool hitEnterKey();
bool getEnterYn(std::string msg);
vmime::string getFolderPathString(vmime::shared_ptr <vmime::net::folder> f);
void printFolders(vmime::shared_ptr <vmime::net::folder> folder, const int level = 0) ;
bool checkNumber(int num, int min, int max);
unsigned int printMenu(const std::vector <std::string>& choices);

void showFlags(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg );
void printStructure(
	vmime::shared_ptr <const vmime::net::messageStructure> s,
	const int level = 0
) ;

void showHeader(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg);
void	showEnvelope(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg);
void extractMessage(vmime::shared_ptr <vmime::net::message> msg);
 void extractAttachments(vmime::shared_ptr <vmime::net::message> msg);
void addMessage(vmime::shared_ptr <vmime::net::folder> f);
void copyMessage(vmime::shared_ptr <vmime::net::folder> f,
	vmime::shared_ptr <vmime::net::message> msg);
vmime::shared_ptr <vmime::net::folder> changeFolder(int mode,  vmime::shared_ptr <vmime::net::store> st );

std::vector <vmime::shared_ptr <const vmime::attachment> > getAttachments(vmime::shared_ptr <vmime::net::message> msg);

void printAttachment(vmime::shared_ptr <const vmime::attachment> attch);
bool saveAttachment(std::string name,  vmime::shared_ptr <const vmime::attachment> attch);

bool saveNetMessage( vmime::shared_ptr <vmime::net::message> msg );


// global
const std::string LF = "\n";


/**
 *  hitEnterKey
 */
bool hitEnterKey()
{

	std::cout << std::endl;
	std::cout << "Please hit Enter key " << std::endl;
	std::cout << std::endl;

	std::string line;
	getline(std::cin, line);

	if( line.empty() ) {
		return true;
	}

	return false;
}


/**
 *  getEnterYn
 */
bool getEnterYn(std::string msg)
{
	std::cout << msg << " [Y/n] ";
	std::cout.flush();

	std::string answer;
	getline(std::cin, answer);

	if ( answer.empty() || (answer[0] == 'Y' ) || ( answer[0] == 'y') ) {
			return true;
	}

	return false;
}



 /**
 *  getFolderPathString
 */
vmime::string getFolderPathString(vmime::shared_ptr <vmime::net::folder> f) {

	const vmime::string n = f->getName().getBuffer();

	if (n.empty()) {  // root folder

		return "/";

	} else {

		vmime::shared_ptr <vmime::net::folder> p = f->getParent();
		return getFolderPathString(p) + n + "/";
	}
}


/** Print folders and sub-folders on the standard output.
  *
  * @param folder current folder
  */
void printFolders(vmime::shared_ptr <vmime::net::folder> folder, const int level) 
{

	for (int j = 0 ; j < level * 2 ; ++j) {
		std::cout << " ";
	}

	const vmime::net::folderAttributes attr = folder->getAttributes();
	std::ostringstream attrStr;

	if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ALL) {
		attrStr << " \\use:All";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ARCHIVE) {
		attrStr << " \\use:Archive";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_DRAFTS) {
		attrStr << " \\use:Drafts";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_FLAGGED) {
		attrStr << " \\use:Flagged";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_JUNK) {
		attrStr << " \\use:Junk";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_SENT) {
		attrStr << " \\use:Sent";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_TRASH) {
		attrStr << " \\use:Trash";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_IMPORTANT) {
		attrStr << " \\use:Important";
	}

	if (attr.getFlags() & vmime::net::folderAttributes::FLAG_HAS_CHILDREN) {
		attrStr << " \\flag:HasChildren";
	}
	if (attr.getFlags() & vmime::net::folderAttributes::FLAG_NO_OPEN) {
		attrStr << " \\flag:NoOpen";
	}

	for (size_t i = 0, n = attr.getUserFlags().size() ; i < n ; ++i) {
		attrStr << " \\" << attr.getUserFlags()[i];
	}

	std::cout << getFolderPathString(folder);
	std::cout << " " << attrStr.str();
	std::cout << std::endl;

	std::vector <vmime::shared_ptr <vmime::net::folder> > subFolders = folder->getFolders(false);

	for (unsigned int i = 0 ; i < subFolders.size() ; ++i) {
		printFolders(subFolders[i], level + 1);
	}
}


/**
 *  checkNumber
 */
bool checkNumber(int num, int min, int max)
{
	if (num >= min && num <=  max) {
		return true;
	}

	std::cerr << "invalid number: " << num << " ( "<< min << " - " << max << " ) "<< std::endl;
	return false;
}


/** Print a menu on the standard output.
  *
  * @param choices menu choices
  */
unsigned int printMenu(const std::vector <std::string>& choices) {

	std::cout << std::endl;
	std::cout << "  0 : quit" << std::endl;
	for (unsigned int i = 0 ; i < choices.size() ; ++i) {
		std::cout << "  " << (i + 1) << " : " << choices[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << "   Your choice? [0-" << choices.size() << "] ";
	std::cout.flush();

	std::string line;
	std::getline(std::cin, line);

	std::istringstream iss(line);

	unsigned int choice;
	iss >> choice;

	std::cout << std::endl;

	return choice;
}









/**
 *  showFlags
 */
void showFlags(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg )
{
    std::cout << "show message flags" << std::endl;
 
    f->fetchMessage(msg, vmime::net::fetchAttributes::FLAGS);

    int flags = msg->getFlags();
	if (flags & vmime::net::message::FLAG_SEEN) {
					std::cout << "FLAG_SEEN" << std::endl;
	}
	
    if (flags & vmime::net::message::FLAG_RECENT) {
					std::cout << "FLAG_RECENT" << std::endl;
	}
					
    if (flags & vmime::net::message::FLAG_REPLIED) {
				std::cout << "FLAG_REPLIED" << std::endl;
	}

	if (flags & vmime::net::message::FLAG_DELETED) {
				std::cout << "FLAG_DELETED" << std::endl;
	}

    if (flags & vmime::net::message::FLAG_MARKED) {
				std::cout << "FLAG_MARKED" << std::endl;
    }

    if (flags & vmime::net::message::FLAG_PASSED) {
				std::cout << "FLAG_PASSED" << std::endl;
	}

}


/** Print the MIME structure of a message on the standard output.
  *
  * @param s structure object
  * @param level current depth
  */
void printStructure(
	vmime::shared_ptr <const vmime::net::messageStructure> s,
	const int level ) 
{

	for (size_t i = 0 ; i < s->getPartCount() ; ++i) {

		vmime::shared_ptr <const vmime::net::messagePart> part = s->getPartAt(i);

		for (int j = 0 ; j < level * 2 ; ++j) {
			std::cout << " ";
		} // for

		std::cout
			<< (part->getNumber() + 1) << ". "
			<< part->getType().generate()
			<< " [" << part->getSize() << " byte(s)]"
			<< std::endl;

		printStructure(part->getStructure(), level + 1);
	} // for

}


/**
 *  showHeader
  */
void showHeader(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg)
{
    std::cout << "Show message header" << std::endl;

    std::string headers;
    getFullHeaders( f, msg, headers);

	std::cout << std::endl;
	std::cout << headers << std::endl;
	std::cout << "----------" << std::endl;

}


/**
 *  showEnvelope
  */
void	showEnvelope(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg)
{
    std::cout << "Show message envelope" << std::endl;

	vmime::net::fetchAttributes attr(vmime::net::fetchAttributes::ENVELOPE);

	// If you also want to fetch "Received: " fields:
	//attr.add("Received");

	f->fetchMessage(msg, attr);

		std::cout << std::endl;
	std::cout << msg->getHeader()->generate() << std::endl;
	std::cout << "----------"<< std::endl;

}


/**
 *  extractMessage
  */
void extractMessage(vmime::shared_ptr <vmime::net::message> msg)
{

    std::cout << "extract whole message" << std::endl;

    std::vector <vmime::shared_ptr <const vmime::attachment> > attchs = getAttachments(msg);

    int size = attchs.size();
	 if (size > 0) {
                std::cout << "this message has " << size << " attachment(s)" << std::endl;
                std::cout << "extract attachments ?" << std::endl;
                bool ret = getEnterYn("");
                if(ret){
				    extractAttachments(msg);
                    return;
                }
    }


	vmime::utility::outputStreamAdapter out(std::cout);
	std::cout << std::endl;
	msg->extract(out);
	std::cout << std::endl;
	std::cout << "----------" << std::endl;

}



/**
 *   extractAttachments
  */
void extractAttachments(vmime::shared_ptr <vmime::net::message> msg)
{

    std::cout << "extract attachments" << std::endl;

    std::vector <vmime::shared_ptr <const vmime::attachment> > attchs = getAttachments(msg);

    int attchs_size  = attchs.size();
	if (attchs_size ==  0) {
	        std::cout <<  "this message has No attachments" << std::endl;
            return;
    }
	
//Content-Type: text/plain
//Content-Transfer-Encoding: 8bit
//Content-Disposition: inline
//This is a test e-mail. 

    std::vector<std::string> attch_list;
    for(int i=0; i < attchs_size; i++)
	{
		auto att = attchs[i];
		vmime::word att_name =  att->getName(); 
		std::string str_name = att_name.getBuffer();
		vmime::mediaType type =  att->getType();
		std::string str_type = type.getType();
		vmime::encoding encoding = att->getEncoding();
		std::string str_encoding = encoding.getName();
        std::string line = str_name + " : " + str_type + " : " + str_encoding;
        attch_list.push_back(line);
	} // for

	vmime::utility::outputStreamAdapter out(std::cout);

	while(1)
	{
	
        int num = printMenu(attch_list);
		if(num == 0){
			break;
		} else {
		    bool ret1 = checkNumber(num, 1, attchs_size );
		    if(!ret1){
				continue;
		    }
        }

		int index = num - 1;
		int max = attchs_size - 1;
		if(index < 0){
			index = 0;
		} else if(index > max){
			index = max;
		}

		auto attch = attchs[index];
		vmime::mediaType type =  attch->getType();
		std::string str_type = type.getType();
		vmime::word att_name =  attch->getName(); 
		std::string str_name = att_name.getBuffer();
		vmime::encoding encoding = attch->getEncoding();
		std::string str_encoding = encoding.getName();
	
		if( str_type == "text" ){
                printAttachment(attch);
		} else if( str_type == "application" ){
                if(str_name.empty()){
                    if( str_encoding == "7bit" ){
                            printAttachment(attch);
                    }
                } else {
			            std::cout << "save to " << str_name <<  " ?" << std::endl;
			            bool ret3 = getEnterYn("");
			            if(ret3){
                                 saveAttachment(str_name,  attch)	; 
			            }
                }
		} else if( str_type == "image" ) {
			vmime::word att_name =  attch->getName(); 
			std::string str_name = att_name.getBuffer();
			std::cout << "save to " << str_name <<  " ?" << std::endl;
			bool ret2 = getEnterYn("");
			if(ret2){
                saveAttachment(str_name,  attch)	; 
			}

		}

		hitEnterKey();

	} // while

}


/**
 *   printAttachment
  */
void printAttachment(vmime::shared_ptr <const vmime::attachment> attch)
{

	vmime::utility::outputStreamAdapter out(std::cout);

    vmime::shared_ptr< const  vmime::contentHandler > handler = attch->getData();

    handler->extract(out);
	std::cout << std::endl;
}


/**
 *   saveAttachment
  */
bool saveAttachment(std::string name,  vmime::shared_ptr <const vmime::attachment> attch)
{

    vmime::shared_ptr< const  vmime::contentHandler > handler = attch->getData();

    std::ofstream ofs;                   
     ofs.open(name,  ( std::ios_base::out | std::ios_base::binary) );
	if(!ofs){
					std::cout << "can not open: " << name << std::endl;
					return false;
	}

	vmime::utility::outputStreamAdapter file(ofs);
	handler->extract(file);
	std::cout << "saved: " << name << std::endl;

    return true;
}


/**
 *  addMessage
  */
void addMessage(vmime::shared_ptr <vmime::net::folder> f)
{

        vmime::messageBuilder mb;

		mb.setExpeditor(vmime::mailbox("me@somewhere.com"));

		vmime::addressList to;
		to.appendAddress(vmime::make_shared <vmime::mailbox>("you@elsewhere.com"));
		mb.setRecipients(to);

		mb.setSubject(vmime::text("Test message from VMime"));
		mb.getTextPart()->setText(
		    vmime::make_shared <vmime::stringContentHandler>(
			"Body of test message from VMime"
			)
			);

        vmime::shared_ptr <vmime::message> msg = mb.construct();

		vmime::net::messageSet set = f->addMessage(msg);

		if (set.isEmpty()) {
                std::cout << "Message has successfully been added, "
				        << "but its UID/number is not known." << std::endl;
        } else {
                const vmime::net::messageRange& range = set.getRangeAt(0);

				if (set.isUIDSet()) {
                        const vmime::net::message::uid uid =
						dynamic_cast <const vmime::net::UIDMessageRange&>(range).getFirst();
                        std::cout << "Message has successfully been added, "
						    << "its UID is '" << uid << "'." << std::endl;
                } else {
                            const vmime::size_t number =
							dynamic_cast <const vmime::net::numberMessageRange&>(range).getFirst();
                            std::cout << "Message has successfully been added, "
							    << "its number is '" << number << "'." << std::endl;
				} // if (set.isUIDSet
		} //  		if (set.isEmpty()
}


/**
 *  copyMessage
  */
void copyMessage(vmime::shared_ptr <vmime::net::folder> f,
	vmime::shared_ptr <vmime::net::message> msg)
{

    vmime::net::messageSet set = f->copyMessages(f->getFullPath(),
		vmime::net::messageSet::byNumber(msg->getNumber()));

		if (set.isEmpty()) {
				std::cout << "Message has successfully been copied, "
						          << "but its UID/number is not known." << std::endl;

		} else {
						const vmime::net::messageRange& range = set.getRangeAt(0);

					if (set.isUIDSet()) {

							const vmime::net::message::uid uid =
								dynamic_cast <const vmime::net::UIDMessageRange&>(range).getFirst();

							std::cout << "Message has successfully been copied, "
							          << "its UID is '" << uid << "'." << std::endl;

					} else {

							const vmime::size_t number =
								dynamic_cast <const vmime::net::numberMessageRange&>(range).getFirst();

							std::cout << "Message has successfully been copied, "
							          << "its number is '" << number << "'." << std::endl;
					}
    }
}



/**
 *  changeFolder
  */
vmime::shared_ptr <vmime::net::folder> changeFolder(vmime::shared_ptr <vmime::net::store> st )
{

    std::cout << "Enter folder path (eg. /root/subfolder):" << std::endl;
	std::cout.flush();

	std::string path;
	std::getline(std::cin, path);

	vmime::shared_ptr <vmime::net::folder> newFolder = st->getRootFolder();

		for (std::string::size_type s = 0, p = 0 ; ; s = p + 1) {
						p = path.find_first_of('/', s);
						const std::string x = (p == std::string::npos)
							? std::string(path.begin() + s, path.end())
							: std::string(path.begin() + s, path.begin() + p);

						if (!x.empty()) {
							newFolder = newFolder->getFolder(vmime::utility::path::component(x));
						}

						if (p == std::string::npos) {
							break;
						}
    } // for

	    newFolder->open(vmime::net::folder::MODE_READ_WRITE);

		vmime::size_t count = newFolder->getMessageCount();

		std::cout << std::endl;
		std::cout << count << " message(s) in this folder" << std::endl;
	
    return newFolder;
}


/**
 *  getAttachments
  */
std::vector <vmime::shared_ptr <const vmime::attachment> > getAttachments(vmime::shared_ptr <vmime::net::message> msg)
{

   vmime::shared_ptr <vmime::message> parsedMsg = msg->getParsedMessage();
	std::vector <vmime::shared_ptr <const vmime::attachment> > attchs =
	vmime::attachmentHelper::findAttachmentsInMessage(parsedMsg);
    return attchs;
}



/** 
 *  showBody
  */ 
void showBody( vmime::shared_ptr <vmime::net::message> msg )
{
    std::cout << "show body" << std::endl;
    std::cout << std::endl;

    std::string body;
    std::string media_type;
    std::string charset;
   getBodyContent(msg, body, media_type, charset);

    std::cout << "mediatype: " << media_type << std::endl;
    std::cout << "charset: " << charset << std::endl;

    std::cout << "----------" << std::endl;
    std::cout << body << std::endl;
    std::cout << "----------" << std::endl;

}


/** 
 *  saveNetMessage
  */      
bool saveNetMessage( vmime::shared_ptr <vmime::net::message> msg )
{
  
    std::string file;
    getTimestampFileName("mail", "eml", file);

    std::ofstream ofs(file);
    if(!ofs){
	    std::cout << "can not open: " << file << std::endl;
        return false;
    }

	vmime::utility::outputStreamAdapter out(ofs);
	msg->extract(out);

    ofs.close();

	std::cout << "saved: " << file << std::endl;
    return true;
}


