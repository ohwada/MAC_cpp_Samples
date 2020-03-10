/**
 * Freeimage Sample
 * 2020-01-01 K.OHWADA
 *  reference : https://qiita.com/ignis_fatuus/items/a4ca7c041691fb0f8c77
 */

#include <string> 
#include<iostream>

#include "freeimage_util.hpp"

#include "parse_filename.hpp"

 using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "FreeImage : read write image file" << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];

    // print Version
    cout << "FreeImage : " << FreeImage_GetVersion() << endl;

    string file_title = getFileNameWithoutExt(input);
    string file_ext = getFileNameExt(input);

    string win_title = "FreeImage: "  + file_title;

    string output_copy = file_title + "_copy." + file_ext;
    string output_gray = file_title + "_gray." + file_ext;

    // read Image
    FIBITMAP* bitmap = loadBitmap(input);
        if(!bitmap) {
                cerr << "loadBitmap Failed" << endl;
                return EXIT_FAILURE;
        }

    // print file info
        int width = FreeImage_GetWidth(bitmap);
        int height = FreeImage_GetHeight(bitmap);

    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input << str_size << endl;


    // save Image
bool ret = saveBitmap(output_copy, bitmap);
    if(!ret) {
                cerr << "SaveImage Failed: " << output << endl;
                return EXIT_FAILURE;
    }

    cout << "saved Image: " << output << endl;

        // convert to black and white
        FIBITMAP * grey = 
            FreeImage_ConvertToGreyscale(bitmap);

        if(!grey) {
                // finish if failed to convert
                cerr << "Convert Failed " << endl;
                return EXIT_FAILURE;
        }

    // save Image
    bool ret2 = saveBitmap(output_gray, grey);
    if(!ret2) {
                cerr << "SaveImage Failed: " << output_gray << endl;
                return EXIT_FAILURE;
    }

    cout << "saved Image: " << output_gray << endl;

	return EXIT_SUCCESS;
}

