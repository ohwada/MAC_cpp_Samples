/**
 *  decomp.cpp
 * 2022-06-01 K.OHWADA
 */

// Compressing and decompressing files to/from a ZIP archive 

#include <iostream>
#include <string>
#include <zip.h>
#include "libzippp.h"
#include "file_util.hpp"
#include "zip_util.hpp"


using namespace std;
using namespace libzippp;


/**
 *  main
 */
int main(int argc, char **argv) 
{
	std::string  file("data/sample1.zip");

    if(argc == 2) {
        file = argv[1];
    } else {
        cout << "Usage: " <<argv[0] << " <zipFile> " << endl;
    }

      cout << file << endl;;

  ZipArchive zf(file);

  bool ret = zf.open(ZipArchive::ReadOnly);
    if(!ret) {
        cerr << endl;
        cerr << "cannot open: " << file << endl;
        return EXIT_FAILURE;
    }

  vector<ZipEntry> entries = zf.getEntries();

  vector<ZipEntry>::iterator it;

  for(it=entries.begin() ; it!=entries.end(); ++it) 
{
    ZipEntry entry = *it;

  string name = entry.getName();

    cout << name << endl;

    if( is_zip_dir(name) ) {
// directory
		if ( makeDir( name, 0777) ) {
			cout << "mkdir: " << name << endl;
		}
		continue;
    } 


// file
    auto list = get_parent_list(name);

    for(auto str: list) {
        // cout << str << endl;
		if ( makeDir( str, 0777) ) {
			cout << "mkdir: " << str << endl;
        }
	} // for

 string data = entry.readAsText();

    bool ret1 = writeTextFile(name, data );
    if(ret1) {
        cout << "write: " << name << std::endl;
    } else {
        std::cerr << "cannot write: " << name << std::endl;
    }

    

} // for

  zf.close();

    return EXIT_SUCCESS;
}


// sample1/sample1.txt
// mkdir: sample1
// write: sample1/sample1.txt
// sample1/sample2.txt
// write: sample1/sample2.txt
// sample1/sample3.txt
// write: sample1/sample3.txt
// sample1/

