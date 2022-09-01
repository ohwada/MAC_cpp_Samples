/**
 *  decomp.cpp
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

    string archivepath("test.zip");
    string outputpath("temp");
    string passwd("1234");

    if(argc == 4){
         archivepath = argv[1];
         outputpath = argv[2];
         passwd = argv[3];
    }else if(argc == 3){
         archivepath = argv[1];
         outputpath = argv[2];
    } else if(argc == 2){
         archivepath = argv[1];
    } else {
        cout << "Usage " << argv[0] << " <archivepath> " << endl;
    }

    cout << archivepath << endl;
    cout << outputpath << endl;
    cout << passwd << endl;

     decompress(outputpath, archivepath, passwd, [](std::string_view message) {cout << message << endl; });


    return 0;
   }
