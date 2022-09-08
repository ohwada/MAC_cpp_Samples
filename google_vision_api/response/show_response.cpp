 /**
  * parse_response.c
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include "json_response.hpp"
#include "file_util.hpp"
#include "ocv_show.hpp"

using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    std::string file_json("data/sample_faces_response.json");

    std::string file_input("data/sample_faces.png");

    std::string file_output("sample_faces_out.png");

    std::string text;
    readTextFile(file_json, text );
    if(text.empty()){
        std::cerr << "cannot read: " << file_json << std::endl;
        return EXIT_FAILURE;
    }

    auto vec = parseResponseJson(text);

bool ret = ocv_show(vec,  file_input,  file_output); 
if(!ret){
    return EXIT_FAILURE;
}

	wait_key();

    std::cout << "saved: " << file_output << std::endl;

      return EXIT_SUCCESS;
}


