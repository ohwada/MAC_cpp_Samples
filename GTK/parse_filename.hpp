/**
 * C++ Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 

bool parseFileName(std::string fullpath, std::string &dir, std::string &title, std::string &ext);

std::string getFileNameWithExt(std::string fullpath);

std::string getFileNameWithoutExt(std::string fullpath);

std::string getFileNameExt(std::string fullpath);

void parseFilePath(std::string fullpath, std::string &dir, std::string &basename);

bool parseBaseName(std::string basename, std::string &title, std::string &ext)
;

