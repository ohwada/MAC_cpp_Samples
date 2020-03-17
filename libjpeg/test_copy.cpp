/**
 * libjpeg Sample
 * 2020-02-01 K.OHWADA
 */


#include <string>
#include <iostream>

#include "jpeg.h"

#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    const int JPEG_QUALITY = 90;

    cout << "libjpeg : copy " << endl;

    const char DOT = '.';
    string ver = to_string(JPEG_LIB_VERSION_MAJOR) + DOT  + to_string(JPEG_LIB_VERSION_MINOR);
    cout << "libjpeg version:  " << ver << endl;

    if ( argc < 2 )
    {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];


    // output file name
    string fname = getFileNameWithoutExt(input);
    string output = fname + "_copy.jpg";


    try
    {
        using namespace marengo::jpeg;
        // Constructor expects a filename to load:
        //Image imgOriginal( input );
        Image img( input );

        // Copy construct a second version so we can
        // shrink non-destructively. Not really necessary
        // here, but just to show it can be done :)
        //Image img = imgOriginal;

        img.save(output, JPEG_QUALITY);

    }
    catch( const std::exception& e )
    {
        cerr << "Faild: " << e.what() << endl;
        return EXIT_FAILURE;
    }

	cout << "saved Image: " << output << endl;

	return EXIT_SUCCESS;
}
