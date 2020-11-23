#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// menu function



#include <string>
#include <vector>
#include "response_msg_json.hpp"


// prototype
int printHeaderMenu( std::vector<struct MailMessage> msg_list );
int printMailPartMenu( std::vector<struct MailPart> parts );
int printMenu( std::vector<std::string> list );
void enterReturnKey(void);


/**
 *   printHeaderMenu
 */
int printHeaderMenu( std::vector<struct MailMessage> msg_list )
{
    std::vector<std::string> vec;
    for(auto msg: msg_list){
        std::string subject = msg.subject;
        std::string from = msg.from;
        std::string  str =  subject + std::string(" : ") + from;
        vec.push_back(str);
    }

    return printMenu( vec );
}


/**
 *   printMailPartMenu
 */
int printMailPartMenu( std::vector<struct MailPart> parts )
{
    std::vector<std::string> vec;

    for(auto part: parts){
        std::string filename = part.filename ;
        std::string mimeType = part.mimeType;
        std::string  str =  filename + std::string(" : ") + mimeType;
        vec.push_back(str);
    } // for

    return  printMenu( vec );
}


/**
 *   prinMenu
 */
int printMenu( std::vector<std::string> list )
{

    int size = list.size();
    std::cout << "0 quit "  <<  std::endl;
    for(int i=0; i<size; i++)
    {
        std::cout << (i+1) << " " << list[i] << std::endl;
    } // for

    std::cout << " [ 0 - " <<  size << "] ";

    std::string line;
    std::getline(std::cin, line);
    int choice = stoi(line);

    return choice;
}


/**
 * enterReturnKey
 */
void enterReturnKey(void)
{
    std::cout << "enter return key" << std::endl;
    std::cout << ">" ;

    std::string line;
    std::getline(std::cin, line);
}

