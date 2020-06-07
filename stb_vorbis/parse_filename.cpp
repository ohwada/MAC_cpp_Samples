/**
 * C++ Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include <iostream>

#include "parse_filename.hpp"

using namespace std;


/**
 * parseFilePath
 */
void parseFilePath(string fullpath, string &dir, string &basename)
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
bool parseBaseName(string basename, string &title, string &ext)
{


    int pos = basename.find_last_of('.');
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
bool parseFileName(string fullpath, string &dir, string &title, string &ext)
{

    string basename;
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
string getFileNameWithExt(string fullpath)
{
    string dir;
    string basename;
    parseFilePath(fullpath, dir, basename);
    return basename;
}


/**
 * getFileNameWithoutExt
 */
string getFileNameWithoutExt(string fullpath)
{
    string dir;
    string basename;
    parseFilePath(fullpath, dir, basename);

    string title;
    string ext;
    bool ret = parseBaseName(basename, title, ext);
if(!ret) {
    title = basename;
}
    return title;
}


/**
 * getFileNameExt
 */
string getFileNameExt(string fullpath)
{
    string dir;
    string basename;
    parseFilePath(fullpath, dir, basename);

    string title;
    string ext;
    bool ret = parseBaseName(basename, title, ext);
    if(!ret) {
        ext = "";
    }
    return ext;
}


