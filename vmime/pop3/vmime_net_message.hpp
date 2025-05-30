#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


#include "vmime/vmime.hpp"
#include "vmime_message.hpp"
#include "msg_write.hpp"

// prototype
void extractNetMessage(vmime::shared_ptr <vmime::net::message> msg);
void extractNetAttachments(vmime::shared_ptr <vmime::net::message> msg);
size_t  getNetAttachmentCount(vmime::shared_ptr <vmime::net::message> msg);


/**
 *  extractNetMessage
  */
void extractNetMessage(vmime::shared_ptr <vmime::net::message> msg)
{

    std::cout << "extract whole message" << std::endl;

    size_t count = getNetAttachmentCount( msg );

	 if (count > 0) {
                std::cout << "this message has " << count << " attachment(s)" << std::endl;
                std::cout << "extract attachments ?" << std::endl;
                bool ret = getEnterYn("");
                if(ret){
				    extractNetAttachments(msg);
                    return;
                }
    }

	std::cout << std::endl;
	std::cout << "----------" << std::endl;

    printNetMessage( msg );

	std::cout << "----------" << std::endl;
	std::cout << std::endl;

}


/**
 *   extractNetAttachments
  */
void extractNetAttachments(vmime::shared_ptr <vmime::net::message> net_msg)
{

    std::cout << "extract attachments" << std::endl;

    size_t count = getNetAttachmentCount( net_msg );

	if (count ==  0) {
	        std::cout <<  "this message has No attachments" << std::endl;
            return;
    }

    vmime::shared_ptr <vmime::message> parsed_msg = net_msg->getParsedMessage();

    extractAttachments(parsed_msg);

}


/**
 *   getNetAttachmentCount
  */
size_t  getNetAttachmentCount(vmime::shared_ptr <vmime::net::message> net_msg)
{

    vmime::shared_ptr <vmime::message> parsed_msg = net_msg->getParsedMessage();

    size_t  count = getAttachmentCount( parsed_msg);

    return count;
}
