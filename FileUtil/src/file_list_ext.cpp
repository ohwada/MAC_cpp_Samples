/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// read filenames with spcified extension in directory
// using C++11

// test for getFileList

#include "file_list_ext.hpp"


/**
 * main
 */
int main(int argc, char** argv)
{

// current directory
    std::string path = "src";
    std::string ext = "cpp";

    if(argc == 3) {
        path = argv[1];
        ext = argv[2];
    }else {
        std::cout <<  "Usage: " << argv[0] << " [directory path] [ext] " << std::endl;
    }

    std::vector<std::string> vec;
    std::string error;
    bool ret = getFileList(path, ext, vec, error);

    if(!ret) {
        std::cout << error << std::endl;
        return 1;
    }

    int size = vec.size();
    if(size == 0){
        std::cout << "no files" << std::endl;
        return 1;
    }

    for(int i=0; i<vec.size(); i++) {    
        std::cout << vec[i] << std::endl;
    }

	return EXIT_SUCCESS;
}


// test_parse_filename.cpp
// read_write_text.cpp
// file_list_11.cpp
// file_list_17.cpp
// file_list_ext.cpp


