/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for parseMessageResponseJson

// g++ test/test_src_parseMessageResponseJson.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` 


#include <iostream>
#include <string>
#include "../src/json_response_msg.hpp"
#include "../src/file_util.hpp"
#include "../src/msg_part.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string  file = "samples/sample_msg_response.json";

   if(argc == 2){
        file = argv[1];
    } else {
        cout << "usage: " << argv[0]<< " [responseJsonFile]" << endl;
    }

    cout << "response file: " << file << endl;

    std::string text;
    bool ret1 = readTextFile(file, text);
    if(!ret1 ){
        cout << "readText error: " << file << endl;
        return EXIT_FAILURE;
    }

    string error; 
    bool is_verbose = true;

    struct MailMessage msg;

    bool ret2 = parseMessageResponseJson( 
    text, msg, error, is_verbose) ;

    if(!ret2 ){
        cout << error << endl;
		   return EXIT_FAILURE;
    }

    printMailMessage( msg );

    for(auto part: msg.parts) {
        cout << endl;
        printMailPart( part );
        printMailPartBody(part);
    }

	return EXIT_SUCCESS;
}

// response file: data/sample_msg_response.json
// id: sample id
// subject: sample subject
