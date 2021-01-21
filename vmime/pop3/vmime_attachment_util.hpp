#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// attachment utility


#include "vmime_attachment.hpp"
#include "menu.hpp"


// prototype
void procAttachmentMenu( std::vector< vmime::shared_ptr< const vmime::attachment > > atts );
void procAttachment( vmime::shared_ptr< const vmime::attachment > att,  struct AttachmentInfo info );
void saveAttachmentYn(vmime::shared_ptr< const vmime::attachment > att, std::string fname );


/**
 *  procAttachmentMenu
 */
void procAttachmentMenu( std::vector< vmime::shared_ptr< const vmime::attachment > > atts )
{

    size_t size = atts.size();
    if( size == 0){
        return;
    }

    std::vector<std::string> menu;
    std::vector<struct AttachmentInfo> infos;
    getAttachmentMenu( atts, menu, infos );

    if( size == 1) {
        auto att = atts[0];
        auto info = infos[0];
        procAttachment( att,  info );
        return;
    }

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
            procAttachment( att, info );
        }

    } // while
}


/**
 *  procAttachment
 */
void procAttachment( vmime::shared_ptr< const vmime::attachment > att,  struct AttachmentInfo info )
{

    const std::vector<std::string> menu = { "show", "save"};

    auto fname = info.name;
    auto type = info.type;
    auto label = info.label;

    bool is_save = false;
    int empty = 0; // quit

        std::cout << std::endl;
        std::cout << label << std::endl;

    if(type == "text"){
        std::cout << "this file is text" << std::endl;
        int choice = printMenu( menu, empty );
        if(choice == 0){
            std::cout << "quit" << std::endl;
        } else if (choice == 1){
            // show
            std::cout << std::endl;
            std::cout << "----------" << std::endl;
            printAttachment( att );
            std::cout << "----------" << std::endl;
            std::cout << std::endl;
        } else if (choice == 2){
            is_save = true;
        }
    } else {
        is_save = true;
    }

    if(is_save){
        saveAttachmentYn( att, fname );
    }

}

  
/**
 *  procAttachmentYn
 */
void saveAttachmentYn(vmime::shared_ptr< const vmime::attachment > att, std::string fname )
{

        std::string confirm =  "save to " + fname;
        bool ret1 = getEnterYn(confirm);
        if(ret1){
            bool ret2 = saveAttachment( att,  fname);
            if(ret2){
                std::cout << "saved: " << fname << std::endl;
            } else {
                std::cout << "save faild: " << fname << std::endl;
             }
     } else {
            std::cout << "cancel to save " << std::endl;
    } 

}


