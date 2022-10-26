/**
 *  path.cpp
 * 2022-06-01 K.OHWADA
 */

// https://docs.pocoproject.org/current/Poco.Path.html

#include <iostream>
#include "Poco/Path.h"

using namespace std;


/**
 *  main
 */
int main()
{

    string fpath("aaa/bbb/sample.txt");
    Poco::Path path(fpath);

    cout << fpath << endl;
    cout << "dir0: " << path.directory(0) << endl;
    cout << "dir1: " << path.directory(1) << endl;
    cout << "BaseName: " << path.getBaseName() << endl;
    cout << "FileName: " << path. getFileName() << endl;
    cout << "Extension: " << path.getExtension() << endl;
    cout << "Extension: " << path.getExtension() << endl;
    cout << "toString: " << path.toString() << endl;

    Poco::Path parent("data");
    string fileName("sample.png");

    Poco::Path path2(parent, fileName);
    cout << "path2: " << path2.toString() << endl;


    return 0;
}