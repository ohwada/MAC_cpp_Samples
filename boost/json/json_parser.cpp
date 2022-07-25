/**
 *  json_parser.cpp
 * 2022-06-01 K.OHWADA
 */


// reference : https://boostjp.github.io/tips/json.html

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

using namespace boost::property_tree;


/**
 *  main
 */
int main()
{
    ptree pt;
    read_json("data.json", pt);

    // Data.value
    if (boost::optional<int> value = pt.get_optional<int>("Data.value")) {
        std::cout << "value : " << value.get() << std::endl;
    }
    else {
        std::cout << "value is nothing" << std::endl;
    }

    // Data.str
    if (boost::optional<std::string> str = pt.get_optional<std::string>("Data.str")) {
        std::cout << "str : " << str.get() << std::endl;
    }
    else {
        std::cout << "str is nothing" << std::endl;
    }

    // Data.info
    BOOST_FOREACH (const ptree::value_type& child, pt.get_child("Data.info")) {
        const ptree& info = child.second;

        // Data.info.id
        if (boost::optional<int> id = info.get_optional<int>("id")) {
            std::cout << "id : " << id.get() << std::endl;
        }
        else {
            std::cout << "id is nothing" << std::endl;
        }

        // Data.info.name
        if (boost::optional<std::string> name = info.get_optional<std::string>("name")) {
            std::cout << "name : " << name.get() << std::endl;
        }
        else {
            std::cout << "name is nothing" << std::endl;
        }
    }
    return 0;
}

