/**
 * parse_string.cpp
 * 2020-03-01 K.OHWADA
 */

// parse JSON string
// original : https://github.com/open-source-parsers/jsoncpp/blob/master/example/readFromString/readFromString.cpp

#include "json/json.h"
#include <iostream>

using namespace std;

/**
 * \brief Parse a raw string into Value object using the CharReaderBuilder
 * class, or the legacy Reader class.
 * Example Usage:
 * $g++ readFromString.cpp -ljsoncpp -std=c++11 -o readFromString
 * $./readFromString
 * colin
 * 20
 */


/**
 * main
 */
int main(void) 
{

    const string  RAW_JSON = R"({"Age": 20, "Name": "colin"})";

    const auto  RAW_JSONLength = static_cast<int>( RAW_JSON.length());

    cout << "jsoncpp version: " << JSONCPP_VERSION_STRING << endl;

    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse( RAW_JSON.c_str(),  RAW_JSON.c_str() +  RAW_JSONLength, &root,
                       &err)) {
        cout << "error" << endl;
        return EXIT_FAILURE;
    }
  

  string name = root["Name"].asString();
  int age = root["Age"].asInt();

  cout << "Json: " << endl;
  cout <<  RAW_JSON << endl;

  cout << endl;
  cout << "name: "<< name << endl;
  cout << "age: " << age << endl;

  return EXIT_SUCCESS;
}

// Json: 
// {"Age": 20, "Name": "colin"}
// name: colin
// age: 20
