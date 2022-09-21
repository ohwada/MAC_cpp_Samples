/**
 * chrome.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://takabus.com/tips/175/
#include <iostream>
#include <cstring>

// prototype
void chrome_open(std::string url);


/**
 * chrome_open
 */
void chrome_open(std::string url)
{
    std::string chrome( R"("/Applications/Google Chrome.app/Contents/MacOS/Google Chrome")" );

    std::string str = chrome + std::string(" ") + url;

    char* cmd = (char *)str.c_str();

    std::cout << cmd << std::endl;
    
    errno = 0;

    auto ret = system(cmd);
    if(ret != 0){
        std::cerr << std::strerror(errno) << std::endl;
        std::cout << "please open chrome with " << url << std::endl;
    }

}

