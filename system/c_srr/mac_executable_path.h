#pragma once
/**
 * system sample
 * 2020-07-01 K.OHWADA
 */


 // get executable path for macOS
// work  on macOS only

// reference : https://stackoverflow.com/questions/799679/programmatically-retrieving-the-absolute-path-of-an-os-x-command-line-app/1024933#1024933

// https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html

#include <string.h>
#include <limits.h>

/**
 * macOS
 */
#  include <mach-o/dyld.h>


// prototype
bool getExecutablePath(char * path);


/**
 * getExecutablePath
 * get the full path containing the command name
 * for macOS
 */
bool getExecutablePath(char * path)
{

    uint32_t bufsize = PATH_MAX;
    char buf[PATH_MAX];

    int ret = _NSGetExecutablePath(buf, &bufsize);

    if (ret  != 0) {
        return false;
    }

    strcpy(path, buf);
    return true;
}

