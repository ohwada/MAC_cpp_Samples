/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


#include <iostream>
#include "menu.hpp"
#include "file_util.hpp"


// prototype
void procHtmlMenu(std::string data);
void saveHtmlYn(std::string html);
void printContentYn(std::string data);
void printContent(std::string content);


/**
 *  procHtmlMenu
 */
void procHtmlMenu(std::string data)
{

    const std::vector<std::string> menu = { "show", "save"};

    int empty = 0; // quit

    while(1){
            int choice = printMenu( menu, empty );
            if(choice == 0){
                    std::cout << "quit" << std::endl;
                    break;
            } else if (choice == 1){
                    printContent(data);
            } else if (choice == 2){
                    saveHtmlYn( data);
            }
    } // while
}


/**
 *  saveHtmlYn
 */
void saveHtmlYn(std::string data)
{

        const std::string prefix("mail");
        const std::string ext("html");

        std::string confirm =  "save";
        bool ret1 = getEnterYn(confirm);
        if(ret1){
            std::string fname;
            getTimestampFileName(prefix, ext, fname);

            bool ret2 = writeTextFile( fname, data );
            if(ret2){
                std::cout << "saved: " << fname << std::endl;
            } else {
                std::cout << "save faild: " << fname << std::endl;
             }
        } else {
            std::cout << "cancel to save " << std::endl;
        } 

}

/**
 *  printContentlYn
 */
void printContentYn(std::string data)
{

        std::string confirm =  "show";
        bool ret1 = getEnterYn(confirm);
        if(ret1){
            printContent(data);
        } 

}


/**
 *  printContent
 */
void printContent(std::string content)
{
            std::cout << std::endl;
            std::cout << "----------" << std::endl;
            std::cout << content << std::endl;
            std::cout << "----------" << std::endl;
            std::cout << std::endl;
}
