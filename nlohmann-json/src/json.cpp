/**
 * json.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ json.cpp -o json -std=c++11

// reference : https://qiita.com/yohm/items/0f389ba5c5de4e2df9cf

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

namespace ns {
  // a simple struct to model a person
  struct person {
    std::string name;
    std::string address;
    int age;
  };


/**
 * to_json
 */
  void to_json(json& j, const person& p) {
    j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
  }


 /**
 * from_json
 */
  void from_json(const json& j, person& p) {
// get_to (T & arg) is the same as arg = get <T> ()
    j.at("name").get_to(p.name); 
    j.at("address").get_to(p.address);
    j.at("age").get_to(p.age);
  }
}


/**
 * man
 */
int main(int argc, const char* argv[]) {
  {
    json j;
    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;

// if you specify a key that does not exist, object will be constructed
    j["answer"]["everything"] = 42; 
 
    j["list"] = { 1, 0, 2 };         // [1,0,2]
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };  // {"currentcy": "USD", "value": 42.99}

    std::cout << j << std::endl;
    
    json j2 = {
      {"pi", 3.141},
      {"happy", true},
      {"name", "Niels"},
      {"nothing", nullptr},
      {"answer", {
        {"everything", 42}
                 }
      },
      {"list", {1, 0, 2}},
      {"object", {
        {"currency", "USD"},
        {"value", 42.99}
                 }
      }
    };

    std::cout << j2 << std::endl;

    json empty_list = json::array();  // []
    json empty_obj = json::object();  // {}
    std::cout << empty_list << std::endl << empty_obj << std::endl;
  }

  {
     json j = R"({ "happy": true, "pi": 3.141 })"_json;
    std::cout << j << std::endl;
  }

  {
    std::string s = R"({ "happy": true, "pi": 3.141 } )";
    json j = json::parse(s);
    std::cout << j << std::endl;
    std::cout << j.dump(4) << std::endl;
  }

const char* FILEIN = (char *)"sample.json";
const char* FILEOUT = (char *)"pretty.json";

  {
        std::ifstream fin(FILEIN);
        if(fin) {
            std::cout << "open: " << FILEIN << std::endl;
            std::cout << std::endl;
            json j;
            fin >> j;
            std::ofstream fout(FILEOUT);
            fout << std::setw(4) << j << std::endl;
        } else {
            std::cerr << "can not open: " << FILEIN << std::endl;
            std::cerr << std::endl;
        }
  }

  {
    json j;
    j.push_back("foo");
    j.push_back(1);
    j.push_back(true);
    j.emplace_back(1.78);   // push_backもemplace_backも使える
    // j = ["foo", 1, true, 1.78]
    std::cout << j << std::endl;

    
// You can also loop with iterato
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
      std::cout << *it << '\n';
    }

    // You can also use range-based for
    for (const json& element : j) {
      std::cout << element << '\n';
    }

    // getter/setter

// when fetching an element with operator [], it is necessary to specify the type and convert it.
    const auto tmp = j[0].get<std::string>(); 

    j[1] = 42;
    // bool foo = j.at(2);

// When fetching an element with operator [], it is necessary to specify the type and convert it.
    // const auto i = j[0].get<int>(); 

    if( j == "[\"foo\", 42, true, 1.78]"_json ) {
      std::cout << "two jsons are equal" << std::endl;
    }
    else {
      std::cout << "not equal" << std::endl;
    }

    // other stuff
    std::cout << j.size() << ' ' << j.empty() << std::endl;

    j.clear();
    std::cout << j << std::endl;
  }

  {
    json j = R"( ["foo", 1, true, null, []] )"_json;
    for(const json& x: j) {
      std::string type;
      if( x.is_null() ) { type = "null"; }
      else if( x.is_boolean() ) { type = "boolean"; }
      else if( x.is_number() ) { type = "number"; }
      else if( x.is_object() ) { type = "object"; }
      else if( x.is_array() ) { type = "array"; }
      else if( x.is_string() ) { type = "string"; }
      std::cout << type << std::endl;
      const auto t = x.type();
      switch(t) {
        case json::value_t::null:
          type = "null";
          break;
        case json::value_t::boolean:
          type = "boolean";
          break;
        case json::value_t::number_integer:
          type = "integer";
          break;
        case json::value_t::number_unsigned:
          type = "unsigned";
          break;
        case json::value_t::number_float:
          type = "float";
          break;
        case json::value_t::object:
          type = "object";
          break;
        case json::value_t::array:
          type = "array";
          break;
        case json::value_t::string:
          type = "string";
          break;
        default:
          type = "other";
      } // switch
      std::cout << type << std::endl;
    }
  }

  {
    // create an object
    json o;
    o["foo"] = 23;
    o["bar"] = false;
    o["baz"] = 3.141;

    // also use emplace
    o.emplace("weather", "sunny");

    // special iterator member functions for objects
    for (json::iterator it = o.begin(); it != o.end(); ++it) {
      std::cout << it.key() << " : " << it.value() << "\n";
    }

    // the same code as range for
    for (auto& el : o.items()) {
      std::cout << el.key() << " : " << el.value() << "\n";
    }

    // find an entry
    if (o.find("foo") != o.end()) {
      // there is an entry with key "foo"
    }

    // or simpler using count()
    // int foo_present = o.count("foo"); // 1
    // int fob_present = o.count("fob"); // 0

    // delete an entry
    o.erase("foo");
  }

  {
    std::vector<int> c_vector {1, 2, 3, 4};
    json j_vec(c_vector);
    std::cout << j_vec << std::endl;
    // [1, 2, 3, 4]
  }

  {
    std::map<std::string, int> c_map { {"one", 1}, {"two", 2}, {"three", 3} };
    json j_map(c_map);
    std::cout << j_map << std::endl;
    // {"one": 1, "three": 3, "two": 2 }
  }

  {
    std::string s1 = "Hello, world!";
    json js = s1;
    auto s2 = js.get<std::string>();
    std::cout << js << std::endl << s2 << std::endl;
  }

  {
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
    json j = p;
    std::cout << j << std::endl;

    ns::person p2 = j.get<ns::person>();
    std::cout << p2.name << std::endl;
  }

  {
    json j = R"({"foo": 1, "bar": "hello", "baz": true} )"_json;
    std::vector<std::uint8_t> v_msgpack = json::to_msgpack(j);

    json j2 = json::from_msgpack(v_msgpack);
    std::cout << j2 << std::endl;  // == {"foo": 1, "bar": "hello", "baz": true}
  }

    return 0;
}

// {"answer":{"everything":42},"happy":true,"list":
// [1,0,2],"name":"Niels","nothing":null,"object":
// {"currency":"USD","value":42.99},"pi":3.141}
