/*
 * TGALoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl5.html
 */

/*************************************************************************
　　TGALoader.h

　　TGA Texture Loader

　　Date : October 10, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo :
*************************************************************************/

#ifndef _TGA_LOADER_H_INCLUDED_
#define _TGA_LOADER_H_INCLUDED_

//
//　include
//
#include <stdio.h>
#include <stdlib.h>
#include <string>  
#include <iostream>
#include <fstream>


//////////////////////////////////////////////////////////////////////////
//　　TGALoader class
//////////////////////////////////////////////////////////////////////////
class TGAImage
{
protected:
	char *imageData;
	int width;
	int height;

	const int FORMAT_FULLCOLOR = 2;

	char* 
	alignmentImage(char *src, int width, int height, int bpp, int bit_vertical);

	std::string getImageFormatLabel(int format);
    std::string getOriginLabel(int bit_horizontal, int bit_vertical);

public:
	TGAImage();
	~TGAImage();

	char* getImageData();
	int getWidth();
	int getHeight();
	bool ReadTGA(std::string filename);

};

#endif		//　_TGA_LOADER_H_INCLUDED_


