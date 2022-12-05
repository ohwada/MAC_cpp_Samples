#pragma once
/**
 * file_util.hpp
 * 2020-03-01 K.OHWADA
 */

// read write text file

#include <fstream>
#include <fstream>
#include <string>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <ctime>
#include <sys/stat.h>


// prototype
bool existsFile(std::string file);
int file_exists (char *filename) ;
bool readTextFile1( std::string file, std::string &text );
bool readTextFile2( std::string file, std::vector<std::string> &vec );
bool writeTextFile(std::string file, std::string data );
bool readBinaryFile1(const std::string filepath, std::vector<char> &data);
bool readBinaryFile2(const std::string filepath, std::string &data);
 bool writeBinaryFile1(const std::string filepath, std::vector<char> data);
bool writeBinaryFile2(const std::string filepath, char* data, size_t size);
void dumpBinary(std::vector<char> data, size_t size);
void getTimestampFileName(std::string prefix, std::string ext, std::string &filename);
void getTimestamp(std::string &timestamp);
bool cmpFiles(const std::string& p1, const std::string& p2);
std::string make_path(std::string dir, std::string fname);
bool makeDir(std::string dir, mode_t mode);
bool make_dir(char* dir, mode_t mode);
bool is_dir2(char* path);


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
bool readTextFile1( std::string file, std::string &text )
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
 * readTextFile2
 */
bool readTextFile2( std::string file, std::vector<std::string> &vec )
{

    std::ifstream fin;

    // open input file
    fin.open(file, std::ios::in); 
    if (fin.fail()){ 
        return false;
    }                         

    // read text  by one line
    std::string line;
    while( getline(fin, line) ) {
        vec.push_back( line );
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
 * readBinaryFile1
 */
bool readBinaryFile1(const std::string filepath, std::vector<char> &data)
{

	std::ifstream file(filepath.c_str(), std::ios::binary | std::ios::in);
	if (!file){
		return false;
    }

	char c = file.get();
	for (; file.good(); c = file.get())
	{
		if (file.bad()){
			break;
        }

		data.push_back(c);

	} // for

    file.close();
    return true;
}


/**
 * readBinaryFile2
 */
bool readBinaryFile2(const std::string filepath, std::string &data)
{
    std::vector<char> vec;
    bool ret = readBinaryFile1(filepath, vec);
    if(!ret){
        return false;
    }
    const char NUL = '\0';
    size_t size = vec.size();
    std::string str(size+10, NUL); // 10 margin

    for(int i=0; i<size; i++){
        str[i] = vec[i];
    } // for

    data = str;

    return true;
}


/**
 * writeBinaryFile
 */
bool writeBinaryFile1(const std::string filepath, std::vector<char> vec)
{
    char* data= reinterpret_cast<char*>(&vec[0]);
    size_t size = vec.size();

    return writeBinaryFile2(filepath, data, size);
}


/**
 * writeBinaryFile
 */
bool writeBinaryFile2(const std::string filepath, char* data, size_t size)
{

	std::ofstream file(filepath.c_str(), std::ios::binary | std::ios::out);
	if (!file){
		return false;
    }

    file.write( data, size );

    file.flush();
    file.close();

    return true;
}


/**
 * dumpBinary
 */
void dumpBinary(std::vector<char> data, size_t size)
{
    for(int i=0; i<size; i++) {
        std::cout << std::hex << data[i];
    }
    std::cout << std::endl;
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
 *   cmpFiles
* reference : https://stackoverflow.com/questions/6163611/compare-two-files
 */
bool cmpFiles(const std::string& p1, const std::string& p2) 
{
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

/**
 * make_path
 */
std::string make_path(std::string dir, std::string fname)
{
    const char SLASH = '/';

    std::string path = dir;
    int len = path.size();
    if( path[len - 1] != SLASH){
        path.push_back(SLASH);
    }
    path += fname;
    return path;
}


/**
 * makeDir
 */
bool makeDir(std::string dir, mode_t mode)
{
    return make_dir( (char *)dir.c_str(), mode);
}


/**
 * make_dir
 */
bool make_dir(char* dir, mode_t mode)
{

	if( strlen(dir) == 0 ) {
		return false;
	}

	if( is_dir2(dir) ) {
		return false;
	}

	if ( mkdir(dir, mode) != 0) {
		printf("mkdir faild: %s \n", dir);
        return false;
	}

	if ( chmod(dir, mode) != 0) {
		printf("chmod faild: %s \n", dir);
        return false;
	}

	return true;
} 


/**
 * is_dir
 */
bool is_dir2(char* path)
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

