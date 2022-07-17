/**
 * example2.cpp
 * 2022-06-01 K.OHWADA
 */

// Lookup information.
// original : http://leethomason.github.io/tinyxml2/

// g++ example2.cpp `pkg-config --cflags --libs tinyxml2` -o example2

/* ------ Example 2: Lookup information. ---- */


#include "tinyxml2.h"


/**
 * main
 */
int main()
{
      tinyxml2::XMLDocument doc;
    doc.LoadFile( "dream.xml" );

    // Structure of the XML file:
    // - Element "PLAY"      the root Element, which is the
    //                       FirstChildElement of the Document
    // - - Element "TITLE"   child of the root PLAY Element
    // - - - Text            child of the TITLE Element

    // Navigate to the title, using the convenience function,
    // with a dangerous lack of error checking.
    const char* title = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->GetText();
    printf( "Name of play (1): %s\n", title );

    // Text is just another Node to TinyXML-2. The more
    // general way to get to the XMLText:
    tinyxml2::XMLText* textNode = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->FirstChild()->ToText();
    title = textNode->Value();
    printf( "Name of play (2): %s\n", title );

    return 0;
}
