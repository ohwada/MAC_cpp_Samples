/**
 *  comp.cpp
 * 2022-06-01 K.OHWADA
 */

// Compressing files to a ZIP archive 
// reference : https://suzulang.com/try-libzip-2-compress/

#include <iostream>
#include <string>
#include "libzippp.h"
#include "file_list.hpp"
#include "file_util.hpp"


using namespace std;
using namespace libzippp;


/**
 *  main
 */
int main(int argc,  char* argv[])
{

 	string input("test1");
    string file_zip;

    if(argc == 3){
        input = argv[1];
        file_zip = argv[2];
    } else if(argc == 2){
        input = argv[1];
    } else {
        cout << "Usage: " <<argv[0] << " <dir> <zipFile> " << endl;
    }
 
    if( file_zip.empty() ){
        file_zip = input + ".zip";
    }

    cout << input << endl;
    cout << file_zip << endl;

    if( !isDir(input) ){
            cerr << "not dir: " << input << endl;
            return EXIT_FAILURE;
    }


    vector<string> list;
    string error;
    int ret1 = getFileList(input, list, error );
    if(ret1 != RET__SUCCESS) {
            cerr << "cannot get file list: " << input << endl;
            return EXIT_FAILURE;
    }

    ZipArchive zf(file_zip);

    bool ret2 = zf.open(ZipArchive::Write);
    if(!ret2) {
        cerr << endl;
        cerr << "cannot open: " << file_zip << endl;
        return EXIT_FAILURE;
    }

    zf.addEntry(input);
    cout << "add dir: " << input << endl;

    for(auto file: list)
    {
        auto path = make_path(input, file);
        string text;
        bool ret3 = readTextFile(path, text );
        if(ret3) {
            zf.addData(path, (char *)text.c_str(), text.size() );
            cout << "add file: " << path << endl;
        } else {
            cerr << "cannot read: " << path << endl;
        }
    }

  zf.close();

    return EXIT_SUCCESS;
}

// add dir: test1
// add file: test1/sample1.txt
// add file: test1/sample2.txt
// add file: test1/sample3.txt
