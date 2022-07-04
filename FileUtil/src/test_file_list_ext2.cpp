/**
 * test_file_list_ext.2cpp
 * 2020-03-01 K.OHWADA
 */

// read filenames with spcified extension in directory
// using C++11

// test for getFileList

// g++ test_file_list_ext2.cpp -o list_ext2 -std=c++11


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

    string ext1 = "";

    string ext2 = "";

    if(argc == 4) {
        path = argv[1];
        ext1 = argv[2];
        ext2 = argv[3];
    } else if(argc == 3) {
        path = argv[1];
        ext1 = argv[2];
    }else {
        cout <<  "Usage: " << argv[0] << " [directory path] [ext1] [ext2] " << endl;
    }

    cout << "path: " << path << endl;
    cout << "ext1: " << ext1 << endl;
    cout << "ext2: " << ext2 << endl;

    vector<string> vec;
    string error;

    int ret = getFileListExt2(path, ext1, ext2, vec, error);
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

