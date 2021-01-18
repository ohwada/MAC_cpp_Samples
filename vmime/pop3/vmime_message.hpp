#pragma once
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

#include "vmime/vmime.hpp"
#include "vmime_body_part.hpp"
#include "vmime_attachment_util.hpp"
#include "html_write.hpp"


// prototype
void extractMessage(vmime::shared_ptr <vmime::message> msg);
 void extractAttachments(vmime::shared_ptr <vmime::message> msg);
void showBody( vmime::shared_ptr <vmime::message> msg );
void printTextBody( vmime::shared_ptr <vmime::message> msg );
bool getTextPlainHtml( vmime::shared_ptr <vmime::message> msg, std::string &ret_plain, std::string &ret_html, bool is_debug );


// global
const std::string LF = "\n";



/**
 *   extractAttachments
  */
void extractAttachments(vmime::shared_ptr <vmime::message> msg)
{

    std::cout << "extract attachments" << std::endl;

    std::vector <vmime::shared_ptr <const vmime::attachment> > atts = getAttachments(msg);

    int atts_size  = atts.size();
	if (atts_size ==  0) {
	        std::cout <<  "this message has No attachments" << std::endl;
            return;
    }
	
    std::vector<std::string> menu;
    std::vector<struct AttachmentInfo> infos;

    getAttachmentMenu( atts,  menu,  infos);


    int empty = 0; // quit
    while(1)
    {

            int choice = printMenu( menu, empty );
            if( choice == 0 ){
                break;
            }

            int index = choice - 1;

            if ((index >= 0)&&(index < menu.size() )){
                auto att = atts[index];
                auto info = infos[index];
                procAttachment( att,  info );
            }

    } // while

}





/** 
 *  showBody
  */ 
void showBody( vmime::shared_ptr <vmime::message> msg )
{

    std::cout << "show body" << std::endl;
    std::cout << std::endl;

    std::string plain;
    std::string html;
    bool is_debug = true;

    bool ret = getTextPlainHtml( msg,  plain,  html, is_debug );

    if(ret){
            printContent(plain);
            if( html.length() > 0 ){
                std::cout << "this mail has html" << std::endl;
                procHtmlMenu( html );
            }
    } else {
            std::cout << "not found text body" << std::endl;
    }

}


/** 
 *  printTextBody
  */ 
void printTextBody( vmime::shared_ptr <vmime::message> msg )
{

    std::string plain;
    std::string html;
    bool is_debug = false;

    bool ret = getTextPlainHtml( msg,  plain,  html, is_debug );

    if(ret){
            if( plain.length() > 0 ){
                printContent(plain);
            } else {
                std::cout << "this mail has no plain text" << std::endl;
            }
            if( html.length() > 0 ){
                std::cout << "this mail has html" << std::endl;
            }
    } else {
            std::cout << "not found text body" << std::endl;
    }

}


/** 
 *  getTextPlainHtml
  */ 
bool getTextPlainHtml( vmime::shared_ptr <vmime::message> msg, std::string &ret_plain, std::string &ret_html, bool is_debug )
{

    vmime::shared_ptr<vmime::body> body = msg->getBody();

    size_t 	count = body->getPartCount();

    std::string plain;
    std::string html;
    std::string info;
    bool ret = false;

    if(count == 0){
        getTextBody( body, plain);
        ret = true;
    } else {
        ret = getTextBodyRecursive(0, body, plain,  html, is_debug);
    }

    if(ret){
        ret_plain = plain;
        ret_html = html;
    }

    return ret;
}


