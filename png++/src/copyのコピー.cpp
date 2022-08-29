/**
 * copy.cpp
 * 2020-02-01 K.OHWADA
 */
 
#include<iostream>
#include <string>

#include <png++/png.hpp>

#include"parse_filename.hpp"

using namespace std;


/**
 * file_copy
 */
bool file_copy(string input, string output)
{

    try{

        // read image
        png::image< png::rgba_pixel > image(input);

        int width = image.get_width();
        int height = image.get_height();

        string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
        cout << "loadImage: " << input  << str_size << endl;

        // write image
        image.write(output);

    }
    catch (std::exception const& error)
    {
        cerr << "Faild: " << error.what() << endl;
        return false;
    }


    return true;
}


/**
 * main
 */
int main(int argc, char **argv)
{

  string input("images/uparrow.png");

    if(argc == 2){
        input = argv[1];
    } else {
        cout << "Usage " <<  argv[0] << " <pngFile> " << endl;
    }

    cout << input << endl;

    string fname = getFileNameWithoutExt(input);
    string output = fname + "_copy.png";

    cout << output << endl;

    if( !file_copy(input, output) ) {
        return EXIT_FAILURE;
    }

   cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

// saved: uparrow_copy.png

