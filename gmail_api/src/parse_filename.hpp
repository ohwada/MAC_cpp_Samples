#pragma once
/**
  * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// parse file fullpath to dir name, file name, file extension 

#include <string> 


bool parseFileName(std::string fullpath, std::string &dir, std::string &title, std::string &ext);

std::string getFileNameWithExt(std::string fullpath);

std::string getFileNameWithoutExt(std::string fullpath);

std::string getFileNameExt(std::string fullpath);

void parseFilePath(std::string fullpath, std::string &dir, std::string &basename);

bool parseBaseName(std::string basename, std::string &title, std::string &ext)
;


/**
 * parseFilePath
 */
void parseFilePath(std::string fullpath, std::string &dir, std::string &basename)
{
    int pos  = fullpath.find_last_of('/');
    if (pos == std::string::npos) {
        dir = "";
        basename = fullpath;
    } else {
        dir = fullpath.substr(0,pos+1);
        basename = fullpath.substr(pos+1, fullpath.size()-pos);
    }

}


/**
 * parseBaseName
 */
bool parseBaseName(std::string basename, std::string &title, std::string &ext)
{


    int pos = basename.find('.');
    if (pos == std::string::npos) {
        return false;
    }

    title = basename.substr(0, pos);
    ext = basename.substr(pos+1, basename.size()-pos);

    return true;
}


/**
 * parseFileName
 */
bool parseFileName(std::string fullpath, std::string &dir, std::string &title, std::string &ext)
{

    std::string basename;
    parseFilePath(fullpath, dir, basename);

    bool ret = parseBaseName(basename, title, ext);
    if (!ret) {
        return false;
    }

    return true;
}

/**
 * getFileNameWithExt
 */
std::string getFileNameWithExt(std::string fullpath)
{
    std::string dir;
    std::string basename;
    parseFilePath(fullpath, dir, basename);
    return basename;
}


/**
 * getFileNameWithoutExt
 */
std::string getFileNameWithoutExt(std::string fullpath)
{
    std::string dir;
    std::string basename;
    parseFilePath(fullpath, dir, basename);

    std::string title;
    std::string ext;
    bool ret = parseBaseName(basename, title, ext);
if(!ret) {
    title = basename;
}
    return title;
}


/**
 * getFileNameExt
 */
std::string getFileNameExt(std::string fullpath)
{
    std::string dir;
    std::string basename;
    parseFilePath(fullpath, dir, basename);

    std::string title;
    std::string ext;
    bool ret = parseBaseName(basename, title, ext);
    if(!ret) {
        ext = "";
    }
    return ext;
}

