/**
 * example1.cpp
 * 2022-06-01 K.OHWADA
 */

// Load and parse an XML file.
// original : http://leethomason.github.io/tinyxml2/

// g++ example1.cpp `pkg-config --cflags --libs tinyxml2` -o example1

/* ------ Example 1: Load and parse an XML file. ---- */

#include "tinyxml2.h"


/**
 * main
 */
int main()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "dream.xml" );
    doc.Print();
    return 0;
}
