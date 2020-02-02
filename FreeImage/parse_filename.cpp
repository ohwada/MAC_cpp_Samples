/**
 * C++ Sample
 * 2020-01-01 K.OHWADA
 */

#include <string> 
#include <iostream>


using namespace std;

/**
 * parseFileName
 */
bool parseFileName(string fullpath, string &dir, string &title, string &ext)
{
    string name;

    int pos1  = fullpath.find_last_of('/');
    if (pos1 == std::string::npos) {
        dir = "";
        name = fullpath;
    } else {
        dir = fullpath.substr(0,pos1+1);
        name = fullpath.substr(pos1+1, fullpath.size()-pos1);
    }


    int pos2 = name.find('.');
    if (pos2 == std::string::npos) {
        return false;
    }

    title = name.substr(0, pos2);
    ext = name.substr(pos2+1, name.size()-pos2);

    return true;
}

