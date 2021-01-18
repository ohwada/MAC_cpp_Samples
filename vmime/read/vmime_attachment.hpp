/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for attachment

#include <fstream>
#include "vmime/vmime.hpp"


/** 
 * struct AttachmentInfo
  */
struct AttachmentInfo
{
std::string name;
std::string type;
std::string subtype;
std::string encoding;
std::string label;
};


// prototype
void getAttachmentMenu(
std::vector< vmime::shared_ptr< const vmime::attachment > > atts,  std::vector<std::string> &menu,  std::vector<struct AttachmentInfo> &infos);
void getAttachmentInfo( vmime::shared_ptr< const vmime::attachment > att,  struct AttachmentInfo &info);
bool saveAttachment( vmime::shared_ptr< const vmime::attachment > att,  std::string fname);
void printAttachment(vmime::shared_ptr <const vmime::attachment> attch);


/**
 *  getAttachmentMenu
 */
void getAttachmentMenu(
std::vector< vmime::shared_ptr< const vmime::attachment > > atts,  std::vector<std::string> &menu,  std::vector<struct AttachmentInfo> &infos)
{

    struct AttachmentInfo info;

    for(auto att: atts){
        getAttachmentInfo( att,  info);
        menu.push_back(info.label);
        infos.push_back(info);
    }
}


/**
 *  getAttachmentInfo
 */
void getAttachmentInfo( vmime::shared_ptr< const vmime::attachment > att,  struct AttachmentInfo &info)
{
    const std::string LEFT(" ( "); 
    const std::string RIGHT(" ) "); 
    const std::string SLASH(" / "); 
    const std::string COLON(" : "); 

     std::string name = att->getName().getBuffer();

    vmime::mediaType media_type =	att->getType();
     std::string type = media_type.getType();
     std::string subtype = media_type.getSubType();

	 std::string encoding = 
    att->getEncoding().getName();

    std::string label = name + LEFT + type + SLASH + subtype + COLON + encoding + RIGHT;

    info.name = name;
    info.type = type;
    info.subtype = subtype;
    info.label = label;

}


/**
 *  saveAttachment
 */
bool saveAttachment( vmime::shared_ptr< const vmime::attachment > att,  std::string fname)
{
     std::ofstream ofs;                   
    ofs.open( fname,  ( std::ios_base::out | std::ios_base::binary) );
	   vmime::utility::outputStreamAdapter file(ofs);
        if( !ofs.is_open() ){
            return false;
	    }

        vmime::shared_ptr< const vmime::contentHandler > 	ch = att->getData();
        ch->extract(file);
        return true;
}


/**
 *   printAttachment
  */
void printAttachment(vmime::shared_ptr <const vmime::attachment> attch)
{

	vmime::utility::outputStreamAdapter out(std::cout);

    vmime::shared_ptr< const  vmime::contentHandler > handler = attch->getData();

    handler->extract(out);

}
