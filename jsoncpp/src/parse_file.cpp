/**
 * parse_file.cpp
 * 2020-03-01 K.OHWADA
 */

// parse JSON file
// original : https://github.com/open-source-parsers/jsoncpp/blob/master/example/readFromStream/readFromStream.cpp

#include "json/json.h"
#include <fstream>
#include <iostream>

using namespace std;

/** \brief Parse from stream, collect comments and capture error info.
 * Example Usage:
 * $g++ readFromStream.cpp -ljsoncpp -std=c++11 -o readFromStream
 * $./readFromStream
 * // comment head
 * {
 *    // comment before
 *    "key" : "value"
 * }
 * // comment after
 * // comment tail
 */


/**
 * main
 */
int main(int argc, char* argv[]) 
{
char* file = (char *)"jsons/withComment.json";

    Json::Value root;
    ifstream ifs;

    if(argc == 2) {
        file =  argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <jsonFile> "  << endl;
    }

    cout << "file: " << file << endl;

  ifs.open(file);
    if(!ifs){
        cout << "can not open: " << file << endl;
     return EXIT_FAILURE;
    }

    cout << "open: " << file << endl;

  Json::CharReaderBuilder builder;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    cout << errs << endl;
    return EXIT_FAILURE;
  }

  cout << root << endl;

  cout << endl;
    for(auto itr = root.begin(); itr != root.end(); ++itr) {
        cout <<  *itr << endl;
    }

  return EXIT_SUCCESS;
}

// open: jsons/withComment.json
// "value"
// "python"
// "c++"
// "ruby"
