/**
 * dom_parser.cpp
 * 2022-06-01 K.OHWADA
 */

// parse sample.xml
// reference : https://github.com/jezhiggins/arabica/tree/main/examples/DOM

#include <string>
#include <iostream>
#include <DOM/SAX2DOM/SAX2DOM.hpp>

// prototype
void parse(Arabica::DOM::Element<std::string> element);


/**
 * main
 */
int main(int argc, char* argv[])
{

    std::string file("sample.xml");

  if(argc == 2) {
    file =argv[1];
  } else {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
  } 

    std::cout << "file : " << file << std::endl;

  Arabica::SAX2DOM::Parser<std::string> domParser;

    Arabica::SAX::InputSource<std::string> is;
    is.setSystemId(file);
    domParser.parse(is);

    Arabica::DOM::Document<std::string> doc = domParser.getDocument();
    if(doc == 0)
    {
      std::cerr << "Error parsing " << file << std::endl;
      return 1;
    }

    parse(doc.getDocumentElement());

  return 0;
}


std::string name1;


/**
 *  parse
 */
void parse(Arabica::DOM::Element<std::string> element)
{
    name1 = element.getNodeName();
    // std::cout << "name1 : " << name1 << std::endl;

  if(element.hasAttributes())
  {
    Arabica::DOM::NamedNodeMap<std::string> attrs = element.getAttributes();
    for(size_t a = 0; a != attrs.getLength(); ++a)
    {
      Arabica::DOM::Node<std::string> attr = attrs.item(a);
      std::cout << "att: " << attr.getNodeName() 
                << " value: " << attr.getNodeValue()
                << std::endl;
    } // for ...
  } // if ...  

    std::string name2;
     std::string value1;
     std::string value2;
     std::string value3;

  for(Arabica::DOM::Node<std::string> n = element.getFirstChild(); n != 0; n = n.getNextSibling())
  {
        int type = n.getNodeType();
        // std::cout << "type : "<< type << std::endl;
    switch(type)
    {
      case Arabica::DOM::Node<std::string>::ELEMENT_NODE:
        parse(static_cast<Arabica::DOM::Element<std::string> >(n));
        break;

      case Arabica::DOM::Node<std::string>::TEXT_NODE:
            value1 = n.getNodeValue();
            // std::cout << "value1 : " << value1 << std::endl;
            std::cout << name1 << " : " << value1 << std::endl;
            break;

      case Arabica::DOM::Node<std::string>::CDATA_SECTION_NODE:
            value2 = n.getNodeValue();
            std::cout << "value2 : " << value2 << std::endl;
            break;

      case Arabica::DOM::Node<std::string>::PROCESSING_INSTRUCTION_NODE:
        name2 = n.getNodeName();
        value3 = n.getNodeValue();
        std::cout << "name2 : " << name2 
        << "value3 : " << value3 << std::endl;
         break;
    } // switch ...
  } // for ...

}



