/**
 *  comp_decomp.cpp
 * 2022-06-01 K.OHWADA
 */

// Compressing and decompressing files to/from a ZIP archive  

#include <iostream>
#include "zip_util.h"

using namespace std;


/**
 *  main
 */
int main(int argc, char **argv)
{

    string inputpath("test1");
    string archivepath;

    if(argc == 3) {
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

      compress(inputpath, archivepath, [](std::string_view message) {cout << message << endl; });
   
    return 0;
}

// Compressing test/sample1.txt
// Compressing test/sample2.txt
// Compressing test/sample3.txt
