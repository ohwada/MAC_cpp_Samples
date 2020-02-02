/**
 * Freeimage Sample
 * 2020-01-01 K.OHWADA
 */

// https://qiita.com/ignis_fatuus/items/a4ca7c041691fb0f8c77

#include <string> 
#include<iostream>
#include<FreeImage.h>
#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return 1;
    }

    // specify file name from the command line
    string input = argv[1];

    // show version
    cout << "FreeImage : " << FreeImage_GetVersion() << endl;

    //  create output file name
    string dir;
    string title;
    string ext;
    parseFileName(input, dir, title, ext);
    string output = title + "_gray." + ext;

    try {
        // load JPEG image
        FIBITMAP *image = 
            FreeImage_Load(FIF_JPEG, input.c_str(), JPEG_DEFAULT);

        if(image) {
                cout << "load image from: " << input << endl;
        }
        else
        {
                // finish if failed to load
                cerr << "Load Failed: " << input << endl;
                return 1;
        }
        
        // convert to black and white
        FIBITMAP * grey = 
            FreeImage_ConvertToGreyscale(image);

        if(!grey) {
                // finish if failed to convert
                cerr << "Convert Failed " << endl;
                return 1;
        }
        
        // save image as JPEG
        bool ret = FreeImage_Save(FIF_JPEG, grey, output.c_str(), JPEG_DEFAULT);

        if( ret ) {
                cout << "save image to: " << output << endl;
        }
        else
        {
                // finish if failed to save
                cerr << "Save Failed: " << endl;
                return 1;
        }
    }
    catch(exception& e) {
        cerr << "exception!\n" << e.what() << endl;
        return 1;
    }

    return 0;  
}

