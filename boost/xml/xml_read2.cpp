/**
 * xml_read2.cpp
 * 2022-06-01 K.OHWADA
 */

// read booklist.xml
// reference : http://xoxopigs.com/boost_read_xml

// g++ xml_read2.cpp -o read2 -std=c++11  

#include <iostream>
#include <string>
#include <boost/property_tree/xml_parser.hpp>
 

/**
 * main
 */
int main()
{
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml("booklist.xml", pt);
 
 // get attribute "ISBN" for <book-list> <book>
    if (boost::optional<long long> isbn = 
            pt.get_optional<long long>("book-list.book.<xmlattr>.ISBN"))
        std::cout << "ISBN : " << isbn << std::endl;
 
    // get <book-list> <book> <title>
    if (boost::optional<std::string> title =
            pt.get_optional<std::string>("book-list.book.title"))
        std::cout << "TITLE : " << title << std::endl;
 
    // get <book-list> <book> <author>
    if (auto author = pt.get_optional<std::string>("book-list.book.author"))
        std::cout << "AUTHOR : " << author << std::endl;
 
    return 0;
}

