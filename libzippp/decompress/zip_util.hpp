/**
 * zip_util.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include <vector>

// prototype
std::vector<std::string> get_parent_list(std::string filepath);
bool is_zip_dir(std::string name);


/**
 * get_parent_list
 */
std::vector<std::string> get_parent_list(std::string filepath)
{
    const std::string SLASH("/");

    std::vector<std::string> list;

    std::string buf = filepath;

    std::string::size_type start =  0;

    while(1)
    {
        std::string::size_type pos =  buf.find(SLASH, start);

        if(pos == std::string::npos) {
            break;
        }

         auto dir = buf.substr(0, pos);
        list.push_back(dir);
        start = pos+1;
    } // while

    return list;
}


/**
 *  is_zip_dir
 */
// https://stackoverflow.com/questions/56480947/does-libzip-provides-a-way-to-check-if-zip-file-is-a-directory
bool is_zip_dir(std::string name)
{
 	const char SLASH = '/';
	char last = name.back();
	bool ret = (last == SLASH)? true: false;
 	return ret;
}

