/**
 * rss_parser.cpp
 * 2022-06-01 K.OHWADA
 */

// RSS Parser
// extract the Title from RSS Feeds  
// reference : http://tsuyuguchi.com/masaaki/mt/archives/2007/10/15-0051.php

// g++  rss_parser.cpp -o rss -std=c++11 `pkg-config --cflags --libs libxml++-2.6`


#include <iostream>
#include <libxml++/document.h>
#include <libxml++/parsers/domparser.h>
#include <libxml++/nodes/node.h>
#include <libxml++/nodes/element.h>
#include <libxml++/nodes/textnode.h>

using namespace std;
using namespace xmlpp;


/**
 * main
 */
int main(int argc, char* argv[])
{
  std::string filepath;

    if(argc > 1 ) {
        filepath = argv[1]; //Allow the user to specify a different XML file to parse.
    } else {
        filepath = "sample.xml";
       cout << "Usage: " << argv[0] << " <rssFile> " << endl;
    }

    cout << "filepath: " << filepath << endl;

   DomParser parser;

   // parser.parse_memory( string_rss );
    parser.parse_file(filepath);

   Element *root = parser.get_document()->get_root_node();
   NodeSet items = root->find("//item");

   for( NodeSet::iterator it = items.begin(); 
          it != items.end(); it++ )
    {
        const NodeSet value = (*it)->find( "title" );
        string title = dynamic_cast< Element *>(value[0])
                       ->get_child_text()->get_content();
        cout << "Title: " + title << endl;
   }

   return 0;
}

