#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// file utility
// read write text file

#include <fstream>
#include <string>
#include <vector> 
#include <ctime>
#include <sys/stat.h>


// prototype
bool existsFile(std::string file);
int file_exists (char *filename) ;
bool readTextFile( std::string file, std::string &text );
bool writeTextFile(std::string file, std::string data );
void getTimestampFileName(std::string prefix, std::string ext, std::string &filename);
void getTimestamp(std::string &timestamp);



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

