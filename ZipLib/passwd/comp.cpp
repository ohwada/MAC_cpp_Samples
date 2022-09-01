/**
 *  comp_decomp.cpp
 * 2022-06-01 K.OHWADA
 */

// Compressing and decompressing files to/from a ZIP archive with a password

#include <iostream>
#include "zip_util.h"

using namespace std;


/**
 *  main
 */
int main(int argc, char **argv)
{

    string inputpath("test");
    string passwd("1234");
    string archivepath;

   if(argc == 4) {
         inputpath = argv[1];
         archivepath = argv[2];
         passwd = argv[3];
    } else if(argc == 3) {
         inputpath = argv[1];
         archivepath = argv[2];
    } else if(argc == 2){
        inputpath = argv[1];
    } else {
        cout << "Usage " << argv[0] << " <dir> " << endl;
    }

    cout << inputpath << endl;

if( archivepath.empty() ) {
    archivepath = inputpath + string(".zip");
}

    cout << archivepath << endl;

    cout << passwd << endl;

    compress(inputpath, archivepath, passwd, [](std::string_view message) {cout << message << endl; });
   
    return 0;
}

// Compressing test/sample1.txt
// Compressing test/sample2.txt
// Compressing test/sample3.txt
