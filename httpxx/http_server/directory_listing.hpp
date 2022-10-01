#pragma once
/**
 * directory_listing.hpp
 * 2022-06-01 K.OHWADA
 */


#include "file_util.hpp"
#include "parse_filename.hpp"

// prototype
void list_directory( std::string path,  std::ostringstream &body, std::string &mime);
std::string get_file(std::string path);
void get_mime(std::string ext, std::string &mime, bool &is_text, bool &is_binary);
std::string read_file(std::string file, bool is_text, bool is_binary);


/**
 * list_directory
 */
void list_directory( std::string path,  std::ostringstream &body, std::string &mime)
{
    const std::string NOT_FOUND("<h1> Not Found </h1>");

    std::string file = get_file(path);
  std::cout << path << std::endl;
    std::cout << file << std::endl;

    if( existsFile(file) ) {
        std::string ext = getFileNameExt(file);
        bool is_text = false;
        bool is_binary = false;
        get_mime(ext, mime, is_text, is_binary);
    
        std::cout << ext << std::endl;
        std::cout << mime << std::endl;

        std::string data = read_file(file, is_text, is_binary);
        body << data;
    } else {
        body << NOT_FOUND;
    }
}


/**
 * read_file
 */
std::string read_file(std::string file, bool is_text, bool is_binary)
{
        if( is_text ) {
            std::string text;
            bool ret1 = readTextFile(file, text );
            if(ret1) {
                return text;
            }
        }else if( is_binary ) {
            std::string data;
            bool ret2 = readBinaryFile2(file, data);
            if(ret2) {
                return data;
            }
        }

    return NULL;
}


/**
 * get_file
 */
std::string get_file(std::string path)
{
    const char SLASH = '/';
    const std::string STR_SLASH("/");
    const std::string ROOT("www");
    const std::string INDEX("/index.html");

    std::string file;
    if(path == STR_SLASH ){
        file= ROOT +  INDEX;
    } else  if( path[0] == SLASH ) {
       file = ROOT  + path;
    }
    return file;
}


/**
 * get_mime
 */
void get_mime(std::string ext, std::string &mime, bool &is_text, bool &is_binary)
{
    if(ext=="html"){
           mime = "text/html";
            is_text = true;
    } else if(ext=="txt"){
           mime = "text/plane";
            is_text = true;
    } else if (ext == "png"){
            mime = "image/png";
            is_binary = true;
    } else if (ext == "ico"){
            mime = "image/vnd.microsoft.icon";
            is_binary = true;
    }

    return;
}


