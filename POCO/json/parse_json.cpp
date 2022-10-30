/**
 * parsr_json.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://docs.pocoproject.org/current/Poco.JSON.Parser.html

#include <iostream>
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/PrintHandler.h"
#include "Poco/Dynamic/Var.h"

using namespace std;


/**
 * main
 */
int main()
{

    string json = 
R"({ "name" : "Franky", "children" : [ "Jonas", "Ellen" ] })";

Poco::JSON::Parser parser;
Poco::Dynamic::Var result = parser.parse(json);
parser.reset();
std::ostringstream ostr;
Poco::JSON::PrintHandler::Ptr pHandler = new Poco::JSON::PrintHandler(ostr);
parser.setHandler(pHandler);
parser.parse(json); // ostr.str() == json

cout << "json: " << ostr.str() << endl;


Poco::JSON::Object::Ptr pObject = result.extract< Poco::JSON::Object::Ptr>();
string name = pObject->getValue<std::string>("name");

cout << "name: "<< name << endl;

 Poco::JSON::Array::Ptr pChildren = pObject->getArray("children");

cout << "children: " << endl;
for( auto child: *pChildren) {
    cout <<  child.toString() << endl;
}

    return 0;
}

