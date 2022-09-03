/**
 * xpath_select.cpp'
 * 2022-06-01 K.OHWADA
 */

// original : https://pugixml.org/docs/samples/xpath_select.cpp

#include "pugixml.hpp"

#include <iostream>


/**
 * main
 */
int main()
{
    const char* FILE = "xgconsole.xml";

    const pugi::xpath_query XPATH1("/Profile/Tools/Tool[@AllowRemote='true' and @DeriveCaptionFrom='lastparam']");

    const pugi::xpath_query XPATH2("//Tool[contains(Description, 'build system')]");

    pugi::xml_document doc;
    if (!doc.load_file( FILE)) return -1;

// tag::code[]
    pugi::xpath_node_set tools = doc.select_nodes(XPATH1);

    std::cout << "Tools:\n";

    for (pugi::xpath_node_set::const_iterator it = tools.begin(); it != tools.end(); ++it)
    {
        pugi::xpath_node node = *it;
        std::cout << node.node().attribute("Filename").value() << "\n";
    } // for

       pugi::xpath_node_set build_tools = doc.select_nodes( XPATH2);

        std::cout << "Build tool: ";

    for (pugi::xpath_node_set::const_iterator it = build_tools.begin(); it != build_tools.end(); ++it)
    {
        pugi::xpath_node node = *it;
     std::cout << node.node().attribute("Filename").value() << "\n";
    } // for

// end::code[]

    return 0;
}

// Tools:
// mayabatch.exe
// texbuilder_*.exe
// shaderbuilder_*.exe
// Build tool: jam
