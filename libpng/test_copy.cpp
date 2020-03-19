/**
 * libpng Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <png.hpp>

#include"parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "libpng : copy" << endl;

    cout << "libpng Version: " << PNG_LIBPNG_VER_STRING << endl;


    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output = fname + "_copy.png";


    try{

        // read image
        png::image< png::rgba_pixel > image(input);

        int width = image.get_width();
        int height = image.get_height();

        string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
        cout << "loadImage: " << input  << str_size << endl;

        // write image
        image.write(output);

        cout << "saved Image : " << output << endl;

    }
    catch (std::exception const& error)
    {
        cerr << "Faild: " << error.what() << endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;

}

