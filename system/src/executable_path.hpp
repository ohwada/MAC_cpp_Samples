#pragma once
/**
 * system sample
 * 2020-07-01 K.OHWADA
 */


 // get executable path for macOS

// reference : https://stackoverflow.com/questions/799679/programmatically-retrieving-the-absolute-path-of-an-os-x-command-line-app/1024933#1024933

// https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html

#include <limits.h>
#include <string>


/**
 * macOS
 */
#  include <mach-o/dyld.h>



// prototype
bool  replaceString(std::string src, std::string s1,  std::string s2, std::string &dst);
bool getExecutablePath(std::string &path);
std::string getExecutablePathDir(std::string argv0 );


/**
 * replaceString
 */
bool replaceString(std::string src, std::string s1,  std::string s2, std::string &dst)
{

    std::string::size_type pos = src.find(s1);

    if (pos == std::string::npos) {
        dst = "";
        return  false;
    }
    
    dst = src;
    dst.replace(pos, s1.length(),  s2);
    return true;
}


/**
 * getExecutablePath
 * for macOS
 */
bool getExecutablePath(std::string &path)
{

    uint32_t bufsize = PATH_MAX;
    char buf[PATH_MAX];

    int ret = _NSGetExecutablePath(buf, &bufsize);

    if (ret  != 0) {
        return false;
    }

    path = std::string( buf );
    return true;
}


/**
 * getExecutablePathDir
 * for macOS
 */
std::string getExecutablePathDir(std::string argv0 )
{
    std::string path;
    bool ret1 = getExecutablePath(path);
    if (!ret1) {
        return "";
    }

    static std::string dir;
    bool ret2 = replaceString(path, argv0, "", dir);
    if (!ret2) {
        return "";
    }

    return dir;
}

