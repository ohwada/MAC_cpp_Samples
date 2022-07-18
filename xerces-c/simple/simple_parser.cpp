/**
 * simple_parser.cpp 
 * 2020-03-01 K.OHWADA
 */

// reference : https://asakawajunya.hatenablog.com/entry/20110903/1315041149

// g++  simple_parser.cpp `pkg-config --cflags --libs xerces-c` -o parser


#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

using namespace std;
using namespace xercesc;

// prototype
void write(DOMNode* node);
void writeElement(DOMElement* element);
void writeText(DOMText* text);


/**
 * write
 */
void
write(DOMNode* node) {
	if (node) {
		DOMNode::NodeType type = node->getNodeType();
		if( type == DOMNode::ELEMENT_NODE) {
			writeElement(static_cast<DOMElement*>(node));
		} else if( type == DOMNode::TEXT_NODE) {
			writeText(static_cast<DOMText*>(node));
		}

		DOMNode* child = node->getFirstChild();
		while (child) {
			DOMNode* next = child->getNextSibling();
			write(child);
			child = next;
		}
	}
}


/**
 * writeElement
 */
void
writeElement(DOMElement* element) {
	char* name = XMLString::transcode(element->getTagName());
	cout << "tag    : " << name << endl;
	XMLString::release(&name);

	DOMNamedNodeMap* map = element->getAttributes();
	for (XMLSize_t i = 0; i < map->getLength(); i++) {
		DOMAttr* attr = static_cast<DOMAttr*>(map->item(i));
		char* attr_name  = XMLString::transcode(attr->getName());
		char* attr_value = XMLString::transcode(attr->getValue());
		cout << attr_name << ": "<< attr_value << endl;

		XMLString::release(&attr_name);
		XMLString::release(&attr_value);
	}
}


/**
 * writeText
 */
void
writeText(DOMText* text) {
	XMLCh* buffer = new XMLCh[XMLString::stringLen(text->getData()) + 1];
	XMLString::copyString(buffer, text->getData());
	XMLString::trim(buffer);
	char* content=XMLString::transcode(buffer);
	delete[] buffer;

	cout << "content: " << content << endl;
	XMLString::release(&content);
}


/**
 * main
 */
int main(int argc, char* args[]) {

	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n" << message << "\n";
		XMLString::release(&message);
		return 1;
	}

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true); // optional

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);

	const char* xmlFile = "../data/personal.xml";

	try {
		parser->parse(xmlFile);
		DOMDocument* dom = parser->getDocument();
		write(dom);
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (...) {
		cout << "Unexpected Exception \n";
		return -1;
	}

	delete parser;
	delete errHandler;
	return 0;
}


