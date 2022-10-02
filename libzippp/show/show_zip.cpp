/**
 * show_zip.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/ctabin/libzippp

#include <iostream>
#include "libzippp.h"

using namespace std;
using namespace libzippp;


/**
 * main
 */
int main(int argc, char* argv[])
{
    string file("data/sample1.zip");

    if(argc == 2) {
      	file = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file] " << endl;
    }

    cout << file << endl;

  ZipArchive zf(file);

  bool ret = zf.open(ZipArchive::ReadOnly);
if(!ret){
    cerr << endl;
    cerr << "cannot open: " << file << endl;
    return EXIT_FAILURE;
}

  vector<ZipEntry> entries = zf.getEntries();

    cout << "entries: " << entries.size() << endl;

  vector<ZipEntry>::iterator it;

  for(it=entries.begin() ; it!=entries.end(); ++it) 
{
    ZipEntry entry = *it;

    string name = entry.getName();
    // int size = entry.getSize();

    cout << name << endl;
    // cout << "size: " << size << endl;

    //the length of binaryData will be size
    // void* binaryData = entry.readAsBinary();

    //the length of textData will be size
    // string textData = entry.readAsText();
    // cout <<  textData << endl;

  } // for

  zf.close();
  
    return EXIT_SUCCESS;
}

// sample1/sample1.txt
// sample1/sample2.txt
// sample1/sample3.txt
