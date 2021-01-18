#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// attachment utility


#include "vmime_attachment.hpp"
#include "menu.hpp"

// prototype
void procAttachment( vmime::shared_ptr< const vmime::attachment > att,  struct AttachmentInf info );
void saveAttachmentYn(vmime::shared_ptr< const vmime::attachment > att, std::string fname );


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


