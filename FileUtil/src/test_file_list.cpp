/**
 * test_file_list.cpp
 * 2020-03-01 K.OHWADA
 */

// read filenames with spcified extension in directory
// using C++11

// test for getFileList

// g++ test_file_list.cpp -o list -std=c++11

#include <iostream>
#include "file_list.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

// current directory
    string path = ".";


    if(argc == 2) {
        path = argv[1];
    }else {
        cout <<  "Usage: " << argv[0] << " [directory path] " << endl;
    }

    cout << "path: " << path << endl;

    vector<string> vec;
    string error;

    int ret = getFileList(path, vec, error);
    if(ret != RET__SUCCESS ) {
        printError(ret, path, error);
        return EXIT_FAILURE;
    }


    int size = vec.size();
    if(size == 0){
        cerr << "no files" << endl;
        return EXIT_FAILURE;
    }

     cout << "get "<< size << " fies" << endl;

    printFileList(vec);

	return EXIT_SUCCESS;
}

