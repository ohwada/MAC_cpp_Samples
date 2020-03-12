/**
 * Devil Sample
 * 2020-02-01 K.OHWADA
 * original : https://github.com/LuaDist/libdevil/tree/master/examples/simple_example
 */

//
//-----------------------------------------------------------------------------
//
// DevIL Source Example
// Copyright (C) 2000-2002 by Denton Woods
// Last modified:  4/22/2002
//
// Filename: examples/Simple Example/simple.c
//
// Description: Simplest implementation of an DevIL application.
//              Loads an image and saves it to a new image.
//              The images can be of any format and can be different.
//
//-----------------------------------------------------------------------------

#include <string> 
#include<iostream>

#include <IL/il.h>

#include "parse_filename.hpp"

// macro
#define PRINT_ERROR_MACRO printf("Error: 0x%X\n", (unsigned int)Error)

 using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{
	ILuint	ImgId;
	ILenum	Error;

    cout << "Devil : read write image file" << endl;

	cout << "Devil Version: " << ilGetInteger(IL_VERSION_NUM) << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];

    string file_title = getFileNameWithoutExt(input);
    string file_ext = getFileNameExt(input);

    string output = file_title + "_copy." + file_ext;


	// Initialize DevIL.
	ilInit();

	// Generate the main image name to use.
	ilGenImages(1, &ImgId);

	// Bind this image name.
	ilBindImage(ImgId);

	// Loads the image specified by File into the image named by ImgId.
	bool ret1 = ilLoadImage(input.c_str());
	if (!ret1) {
		cerr << "could not load Image: " << input << endl;
        return EXIT_FAILURE;
	}

	cout << "load Image: " << input << endl;

	// Display the image's dimensions to the end user.
	printf("Width: %d  Height: %d  Depth: %d  Bpp: %d\n",
	       ilGetInteger(IL_IMAGE_WIDTH),
	       ilGetInteger(IL_IMAGE_HEIGHT),
	       ilGetInteger(IL_IMAGE_DEPTH),
	       ilGetInteger(IL_IMAGE_BITS_PER_PIXEL));

	// Enable this to let us overwrite the destination file if it already exists.
	ilEnable(IL_FILE_OVERWRITE);

	// save image
	bool ret2 = ilSaveImage(output.c_str());
	if (!ret2) {
		cerr << "could not save Image: " << output << endl;
        return EXIT_FAILURE;
	}

	cout << "saved Image: " << output << endl;

	// We're done with the image, so let's delete it.
	ilDeleteImages(1, &ImgId);

	// Simple Error detection loop that displays the Error to the user in a human-readable form.
	while ((Error = ilGetError())) {
		PRINT_ERROR_MACRO;
    }

	return EXIT_SUCCESS;

}
