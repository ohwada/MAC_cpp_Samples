/**
 * gen_uuid.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://developer.apple.com/documentation/corefoundation/cfuuid-rci

#include <iostream>
#include <CoreFoundation/CFUUID.h>


/**
 * main
 */
int main()
{
      auto newId = CFUUIDCreate(NULL);
        auto str = CFUUIDCreateString(NULL, newId);
      CFRelease(newId);

    std::cout << str << std::endl;

    return 0;
}

// 0x7fe446c06be0
