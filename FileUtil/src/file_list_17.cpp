/**
 * file_list_17.cpp
 * 2020-03-01 K.OHWADA
 */

// read filenames in directory using C++17
// https://en.cppreference.com/w/cpp/filesystem/directory_iterator

// require option c++17
// g++ file_list_17.cpp -std=c++17 -o list17


#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

// porototype
bool getFileList(std::string path, std::vector<std::string> &vec);


/**
 * getFileList
 */
bool getFileList(std::string path, std::vector<std::string> &vec)
{
    bool ret = std::filesystem::is_directory(path);
    if(!ret) {
        std::cout << "not directory: " << path << std::endl;
        return false;
    }

    for (const auto & entry : std::filesystem::directory_iterator(path)){
        vec.push_back( entry.path() );
    }

    return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{

// current directory
    std::string path = ".";

    if(argc == 2) {
        path = argv[1];
    }else {
        std::cout <<  "Usage: " << argv[0] << " [directory path] " << std::endl;
    }

    std::vector<std::string> vec;
    getFileList(path, vec);

    for(auto x: vec){
        std::cout << x << std::endl;
    }

	return EXIT_SUCCESS;
}

