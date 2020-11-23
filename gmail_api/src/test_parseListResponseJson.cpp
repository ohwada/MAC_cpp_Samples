/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for parseListResponseJson

// g++ src/test_parseListResponseJson.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` 

#include <iostream>
#include <string>
#include <vector>
#include "response_json.hpp"
#include "file_text.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string  file = "list_response.json";

   if(argc == 2){
        file = argv[1];
    } else {
        cout << "usage: " << argv[0] << " [responseJsonFile]" << endl;
    }

// response file
    cout << "response file: " << file << endl;

    std::string text;
    bool ret1= readTextFile(file, text);
    if(!ret1){
        cout << "readText faild: " << file << endl;
    }

    vector<string> vec;
    string error; 
    bool verbose = false;

    //bool ret = readListResponseJsonFile( file, vec, error, verbose); 

    bool ret2 = parseListResponseJson( text, vec, error, verbose); 

    cout << endl;

    if( !ret2 ) {
        cout << error << endl;
        return EXIT_FAILURE;
    }

int size = vec.size();

    for(int i=0; i<size; i++){
        auto id = vec[i];
        cout << i << " ) id: " << id << endl;
    }

	return EXIT_SUCCESS;
}


//response file: data/sample_list_response.json
// 0 ) id: dummy id 1
// 1 ) id: dummy id 2
// 2 ) id: dummy id 3


