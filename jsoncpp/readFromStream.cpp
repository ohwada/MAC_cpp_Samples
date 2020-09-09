/**
 * jsoncpp Sample
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

    Json::Value root;
    ifstream ifs;

    if(argc !=2) {

        cout << "Usage: " << argv[0] << " <jsonFile> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];

  ifs.open(input);
    if(!ifs){
        cout << "can not open: " << input << endl;
     return EXIT_FAILURE;
    }

    cout << "open: " << input << endl;

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

// open: assets/withComment.json
// "value"
// "python"
// "c++"
// "ruby"
