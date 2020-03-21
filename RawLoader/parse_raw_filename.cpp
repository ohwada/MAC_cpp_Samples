/**
 * RawLoader Sample
 * 2020-02-01 K.OHWADA
 */

#include <string>

#include "parse_raw_filename.hpp"

using namespace std;



/**
 * parse_raw_file_param
 */
bool parse_raw_file_param(string filename, int &width, int &height, bool &alphaFlag)
{

	const char UNDERBAR = '_';

	string fname = getFileNameWithoutExt(filename);

	std::vector<std::string> vec = split(fname, UNDERBAR);

	if(vec.size() == 4){
        // vec[0] : file title
		width = str2i(vec[1]);
		height = str2i(vec[2]);
		int alpha = str2i(vec[3]);
        alphaFlag = (alpha==1)? true: false;
	} else {
		return false;
	}

	return true;

}


/**
 * split
 */
std::vector<std::string> split(std::string str, char del) {

// https://www.sejuku.net/blog/49378

    int first = 0;
    int last = str.find_first_of(del);
 
    std::vector<std::string> result;
 
    while (first < str.size()) {
        std::string subStr(str, first, last - first);
 
        result.push_back(subStr);
 
        first = last + 1;
        last = str.find_first_of(del, first);
 
        if (last == std::string::npos) {
            last = str.size();
        }
    }
 
    return result;
}


/**
 * str2i
 */
int str2i(string str)
{
    return std::atoi(str.c_str());
}


