/**
 *  parse_file.cc
 * 2022-06-01 K.OHWADA
 */

// g++ parse_file.cc -o file -std=c++11

// reference : https://qiita.com/ayase/items/58c9e63e96857d83ebd9

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "picojson.h"


/**
 *  main
 */
int main(void)
{
const char* FILEPATH = (char *)"sample.json";

    // read JSON data
    std::ifstream ifs(FILEPATH, std::ios::in);
    if (ifs.fail()) {
        std::cerr << "failed to read: "<< FILEPATH << std::endl;
        return 1;
    }

    const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();


// parse JSON data.
    picojson::value v;
    const std::string err = picojson::parse(v, json);

    if (err.empty() == false) {
        std::cerr << err << std::endl;
        return 1;
    }

    std::cout << "output all once." << std::endl;
    std::cout << v << std::endl;
    std::cout << std::endl;

    std::cout << "look at the parsed data." << std::endl;
    picojson::object& obj = v.get<picojson::object>();
    std::cout << "string: "                         << obj["string"].get<std::string>()       << std::endl;
    std::cout << "number_double: "                  << obj["number_double"].get<double>()     << std::endl;
    std::cout << "number_integer: "                 << obj["number_integer"].get<double>()    << std::endl;
    std::cout << "boolean_true: " << std::boolalpha << obj["boolean_true"].get<bool>()        << std::endl;
    std::cout << "boolean_false: "<< std::boolalpha << obj["boolean_false"].get<bool>()       << std::endl; 
    std::cout << "array: ";
    picojson::array& ary = obj["array"].get<picojson::array>();
    for (const auto& e : ary) {  // vectorをrange-based-forでまわしている。
        std::cout << e.get<std::string>() << " ";
    }
    std::cout << "\n\n";

    std::cout << "turn the loop." << std::endl;

// rotate the map by range-based-for.
    for (const auto& p : obj) { 
        std::cout << p.first << ": " << p.second.to_str() << std::endl;
    }

    return 0;
}

// look at the parsed data.
// string: TEST 0
// number_double: 123.456
// number_integer: 123456

