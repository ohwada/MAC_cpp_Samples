#pragma once
/**
  * vmime sample
 * 2020-07-01 K.OHWADA
 */

// file utility

#include <fstream>
#include <string>
#include <vector> 
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>

// prototype
bool existsFile(std::string file);
int file_exists (char *filename) ;
bool readTextFile( std::string file, std::string &text );
bool writeTextFile(std::string file, std::string data );
void getTimestampFileName(std::string prefix, std::string ext, std::string &filename);
void getTimestamp(std::string &timestamp);
bool getFileList(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &error);
bool isDir(char* path);
bool match_ext(std::string str, std::string ext);



/**
 * existsFile
 */
bool existsFile(std::string file)
{
    int ret = file_exists( (char *)file.c_str() );
    bool res = (ret == 0)?true:false;
    return res;
}


/**
 * file_exists
 * @ return 0 : exists, 1 : stat failed
 */
int file_exists (char *filename) 
{
  struct stat buffer;   
  return stat(filename, &buffer);
}


/**
 * readTextFile
 */
bool readTextFile( std::string file, std::string &text )
{
    const std::string LF = "\n";

    std::ifstream fin;

    // open input file
    fin.open(file, std::ios::in); 
    if (fin.fail()){ 
        return false;
    }                         

    // read text  by one line
    std::string line;
    while( getline(fin, line) ) {
        text += line + LF;
    }

    return true;
}


/**
 * writeTextFile
 */
bool writeTextFile(std::string file, std::string data )
{
    std::ofstream fout; 

    // open input file
    fout.open(file, std::ios::out); 
    if (fout.fail()){ 
        return false;
    } 

    // write to output file
    fout<< data;
    fout.close();

    return true;
}



/** 
 *  getTimestampFileName
  */ 
void getTimestampFileName(std::string prefix, std::string ext, std::string &filename)
{
    std::string timestamp;
    getTimestamp(timestamp);

    filename = prefix + std::string("_") + timestamp + std::string(".") + ext;

}


/** 
 *   getTimestamp
 */
void getTimestamp(std::string &timestamp)
{

    const std::string format("%Y%m%d%H%M%S");

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    time_t now = std::time(nullptr);

    std::tm *tm = std::localtime(&now);

    std::strftime(buf, BUFSIZE, (char *)format.c_str(), tm);

    timestamp = std::string( buf );
}


/**
 * getFileList
 */
bool getFileList(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &error)
{

    char* path = (char *)str_path.c_str();

    int ret = isDir(path);
    if(ret == -1) {
        error = std::string("not found: ") + path;
        return false;
    } else if (ret == 0) {
        error = std::string("not directory: ") + path;
        return false;
    }

    DIR *dir;
    dir = opendir(path);
    if (!dir) {
        error = strerror(errno) + std::string(" : ") +path;
        return false;
    }

    const std::string DOT = (char *)".";
    const std::string TWO_DOT = (char *)"..";
    struct dirent * ent;

    while ((ent = readdir (dir)) != NULL) {
        std::string file = std::string( ent->d_name );
        if (( file == DOT  )||( file == TWO_DOT )){
            continue;
        }
        bool ret = match_ext(file, ext);
        if(ret) {
            vec.push_back( std::string( ent->d_name ) );
        }
    } // while

    closedir (dir);

    return true;
}


/**
 * isDir
 */
bool isDir(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return false;
    }

    mode_t m = sb.st_mode;
    bool res = ( S_ISDIR(m) )? true: false;
    return res;        
}


/**
 * match_ext
 */
bool match_ext(std::string str, std::string ext)
{
    const std::string DOT = (char *)".";
    std::string dot_ext = DOT + ext;
    int pos = str.rfind(dot_ext );
    bool ret = (pos == std::string::npos)?false:true;
    return ret;
}
