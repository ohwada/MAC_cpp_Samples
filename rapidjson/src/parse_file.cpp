/**
 * parse_file.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ parse_file.cpp -o file -std=c++11

// reference : https://qiita.com/mink0212/items/a4a46250c8c4038d9356

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>


/**
 * main
 */
int main(int argc, char **argv) 
{
    char* file = (char *)"pets.json";

    if (argc == 2) {
        file = argv[1];
    } else {
        std::cout << "Usage: " << argv[0] << " <jsonlFile> " << std::endl;
    }

    std::cout << "file: " << file << std::endl;

    std::cout << "---- file read ----" << std::endl;
    std::ifstream ifs(file);
    rapidjson::IStreamWrapper isw(ifs);

    std::cout << "---- file parse ----" << std::endl;
    rapidjson::Document doc;
    doc.ParseStream(isw);

    std::cout << "---- string ----" << std::endl;
    const char* a = doc["pets"].GetString();
    std::cout << "pets value:" << a << std::endl;

    return 0;
}

// ---- string ----
// pets value:dog
