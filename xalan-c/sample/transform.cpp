/**
 * transform.cpp
 * 2022-06-01 K.OHWADA
 */

// transform file sample.xml according to the conversion rules written in file sample.xsl
// reference : https://ownway.info/XML/xalan/simple/xslt

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

using namespace std;
using namespace xercesc;
using namespace xalanc;


/**
 * main
 */
int main() 
{
  // initialize Xerces & Xalan-C ++
    XMLPlatformUtils::Initialize();
    XalanTransformer::initialize();

  // transform document
  XalanTransformer transformer;
  transformer.transform("sample.xml", "sample.xsl", cout);

  XalanTransformer::terminate();

  return 0;
}


