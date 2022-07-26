/**
 * to_json.cpp
 * 2020-03-01 K.OHWADA
 */

// convert  Json::Value object to JSON string
// original : https://github.com/open-source-parsers/jsoncpp/blob/master/example/stringWrite/stringWrite.cpp

#include "json/json.h"
#include <iostream>

using namespace std;

/** \brief Write a Value object to a string.
 * Example Usage:
 * $g++ stringWrite.cpp -ljsoncpp -std=c++11 -o stringWrite
 * $./stringWrite
 * {
 *     "action" : "run",
 *     "data" :
 *     {
 *         "number" : 1
 *     }
 * }
 */


/**
 * main
 */
int main(void) 
{

    Json::Value root;
    Json::Value data;

// sample
    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;

    Json::StreamWriterBuilder builder;
    string json_file = Json::writeString(builder, root);
    cout << json_file << endl;

    return EXIT_SUCCESS;
}

// {
// "action" : "run",
// "data" : 
// {
//		"number" : 1
// }
// }

