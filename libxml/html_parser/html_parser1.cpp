/**
 * html_parser1.cpp
 * 2022-06-01 K.OHWADA
 */

// display "a" tag and "href" content
// https://nantonaku-shiawase.hatenablog.com/entry/2012/04/30/231235

// g++  html_parser1.cpp -o parser1 `xml2-config --cflags` `xml2-config --libs`

#include <libxml/HTMLparser.h>
#include <iostream>

using namespace std;

// prototype
void FindInfo(xmlNode*& element);


/**
 * main
 */
int main() 
{
	// Structure for HTML
	htmlDocPtr doc;

	char* file = (char *)"sample.html";
	char* enc = (char *)"utf-8";

	// read html
	doc = htmlReadFile(file, enc, HTML_PARSE_RECOVER);
	if(!doc){
		cerr << "can not read: "<< file<< endl;
		return 1;
	}

	htmlNodePtr root = xmlDocGetRootElement(doc);
		if (!root) {
			cerr << "can not get root "<< endl;
			return 1;
		}

		FindInfo(root);

	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlCleanupCharEncodingHandlers();

	return 0;
}


/**
 * FindInfo
* recursive call
 */
void FindInfo(xmlNode*& element) 
{
const xmlChar* A = (xmlChar*)"a";
const xmlChar* HREF = (xmlChar*)"href";

	for (htmlNodePtr node = element; node != NULL; node = node->next) {
		// cout << "type: "<< node->type << endl;
		if (node->type == XML_ELEMENT_NODE) {
// display if the content of the node is "a" tag and "href" is included in attribute
			cout << "node: " << node->name << endl;
			if( xmlStrcmp(node->name, A) == 0){
				for(xmlAttrPtr attr = node->properties; attr != NULL; attr = attr->next){
					cout << "attr: "<< attr->name << endl;
					if(xmlStrcmp(attr->name, HREF) == 0){
						cout << "attr value: "<< attr->children->content << endl;
						cout << "a href: "<< node->children->content << endl;
					}
				}
			}

// Recursive read
			if(node->children != NULL)
			{
				FindInfo(node->children);
			}
		}
	}
}

