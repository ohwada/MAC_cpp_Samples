/**
 * jsoncpp Sample
 * 2020-03-01 K.OHWADA
 */

// parse sample JSON file
// reerence : http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html

#include <iostream>
#include <fstream>
#include "json/json.h"

using namespace std;

/**
 * main
 */
int main(void) 
{

    Json::Value root; 

    string input = "assets/sample.json";

    ifstream ifs;

  ifs.open(input);
    if(!ifs){
        cout << "can not open: " << input << endl;
     return EXIT_FAILURE;
    }

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        cout << errs << endl;
        return EXIT_FAILURE;
    }

    cout << root << endl;


// Get the value of the member of root named 'encoding',
// and return 'UTF-8' if there is no such member.
    cout << endl;
    string encoding = root.get("encoding", "UTF-8" ).asString();
    cout << "encoding: "  << encoding << endl;
   
// Try other datatypes. Some are auto-convertible to others.
    int indentLength = root["indent"].get("length", 3).asInt();
    cout << "indentLength: " << indentLength << endl;
    bool indentUseSpace = root["indent"].get("use_space", true).asBool();
    cout << std::boolalpha << "indentUseSpace: " << indentUseSpace << endl;


// Get the value of the member of root named 'plug-ins'; return a 'null' value if
// there is no such member.
    Json::Value plugins = root["plug-ins"];

// Iterate over the sequence elements.
    cout << endl;
    cout << "plugins: " << endl;
    for ( int index = 0; index < plugins.size(); ++index ){
        string plugin = plugins[index].asString();
        cout << plugin << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}

// encoding: UTF-8
// indentLength: 3
// indentUseSpace: true
// plugins: 
// python
// c++
// ruby

