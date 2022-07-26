/**
 * parse_person.cpp
 * 2020-03-01 K.OHWADA
 */

// parse parson JSON file

#include <fstream>
#include <iostream>
#include <string>
#include "json/json.h"

using namespace std;


/**
 * readJson
 */
bool readJson(string file, string &name, int* age, string &error) 
{
    Json::Value root;
    ifstream ifs;

    ifs.open(file);
    if(!ifs){
        error = "can not open: " +file;
        cout << error << endl;
     return false;
    }

    cout << "open: " <<file << endl;

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        error = errs;
        cout << error << endl;
        return false;
  }

  cout << root << endl;


    Json::Value sv_name = root.get("name",  Json::nullValue );
    Json::Value sv_age = root.get("age",  Json::nullValue );

    if( sv_name.isNull() ){
        error = "not found name";
        return false;
    } else {
        name = sv_name.asString();
    }

   if( sv_age.isNull() ){
        error = "not found age";
        return false;
    } else if ( sv_age.isNumeric() ) {
        *age = sv_age.asInt();	
    } else {
        string str_age = sv_age.asString();	
        *age = stoi(str_age);
    }

    return true;
}



/**
 * main
 */
int main(int argc, char* argv[]) 
{

    string file = "jsons/taro.json";

    if(argc ==2) {
   file = argv[1];
} else {
        cout << "Usage: " << argv[0] << " <jsonFile> "  << endl;
    }

    cout << "file: " << file << endl;

    string name;
    int age;
    string error;
    bool ret = readJson(file, name, &age, error);

    if(!ret){
        cout << "error: " << error << endl;
     return EXIT_FAILURE;
    }

    cout << "name: " << name << endl;
    cout << "age: " << age << endl;

  return EXIT_SUCCESS;
}


// open: assets/taro.json
// {
// 	"age" : 30,
// 	"name" : "taro"
// }
// name: taro
// age: 30

