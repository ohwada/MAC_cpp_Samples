/**
 * xml_string.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/todanano/items/d70ad0867193cec06a2f

// g++ xml_string.cpp -o string -std=c++11

#include <iostream>
#include <string>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>


/**
 * xml string
 */
std::string Xml = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<soapenv:Envelope xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\
        <soapenv:Body>\
                <soapenv:Fault>\
                        <faultcode>ServerFaultCode</faultcode>\
                        <faultstring>Cannot complete login due to an incorrect user name or password.</faultstring>\
                        <detail>\
                                <InvalidLoginFault xmlns=\"urn:vim25\" xsi:type=\"InvalidLogin\"></InvalidLoginFault>\
                        </detail>\
                </soapenv:Fault>\
        </soapenv:Body>\
</soapenv:Envelope>\
";


// prototype
void show_xml(boost::property_tree::ptree &pt, int indent = 0);


/**
 * show_xml
 */
void show_xml(boost::property_tree::ptree &pt, int indent) {
    for (auto &it : pt) {
        if (it.first == "<xmlattr>") {
            continue;
        }
        std::string attr;
        bool no_child = true;
        for (auto &itt : it.second.get_child("")) {
            if (itt.first == "<xmlattr>") {
                for (auto &ittt : itt.second.get_child("")) {
                    attr += " " + ittt.first + "=\"" + boost::lexical_cast<std::string>(ittt.second.data()) + "\"";
                }
                continue;
            }
            no_child = false;
        }
        for (int i = 0; i < indent; ++i) {
            std::cout << "\t";
        }
        std::cout << "<" << it.first << attr << ">";
        if (no_child) {
            std::cout << it.second.data();
        } else {
            std::cout << std::endl;
            show_xml(it.second, indent + 1);
            for (int i = 0; i < indent; ++i) {
                std::cout << "\t";
            }
        }
        std::cout << "</" << it.first << ">" << std::endl;
    }
}


/**
 * main
 */
int main(int, char **) 
{
    boost::property_tree::ptree pt;
    std::stringstream ss(Xml);
    boost::property_tree::read_xml(ss, pt);

    try {
        show_xml(pt);
    } catch (std::exception const &ex) {
        std::cout << "xml parse error." << std::endl;
    }

    return 0;
}


