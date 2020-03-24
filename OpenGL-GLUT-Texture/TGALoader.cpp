/*
 * TGALoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl5.html
 */

// this sample support fullcolor  uncompressed tga format
// support origin left bottom and left top

/*************************************************************************
　　TGALoader.cpp

　　TGA Texture 

　　Date : October 10, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo :
*************************************************************************/

//
//　include
//
#include <stdio.h>
#include "TGALoader.hpp"


//////////////////////////////////////////////////////////////////////////
//　　TGAImage class
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
//　　TGAImage
//　　Desc : Constructor
//-----------------------------------------------------------------------------------------------------
TGAImage::TGAImage()
{
	imageData = NULL;
	width = 0;
	height = 0;
}

//---------------------------------------------------------------------------------------------------
//　　‾TGAImage
//　　Desc : Destructor
//---------------------------------------------------------------------------------------------------
TGAImage::~TGAImage()
{
	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}
}


//---------------------------------------------------------------------------------------------------
//　　‾TGAImage
//　　Desc : getter
//---------------------------------------------------------------------------------------------------

/** 
 * getImageData
 */
char* TGAImage::getImageData() {
	return imageData;
}


/** 
 * getWidth
 */
int TGAImage::getWidth() {
	return width;
}


/** 
 * getHeight
 */
int TGAImage::getHeight() {
	return height;
}


//---------------------------------------------------------------------------------------------------
//　　ReadTGA
//　　Desc :  Read TGA file
//---------------------------------------------------------------------------------------------------
bool TGAImage::ReadTGA(std::string filename)
{

	char header[18]; 

	//　Open file
	FILE* fp = fopen(filename.c_str(),"rb");
	if (fp == NULL )
	{
		std::cout << "Error : Could not open file \n";
		std::cout << "File Name : " << filename << std::endl;
		return false;
	}

	//　Read header information
    size_t num = sizeof(header);
	size_t ret1 = fread(header, 1, num, fp);
    if(ret1 < num){
		std::cout << "Could not read header : " << filename << std::endl;
		return false;
    }

	std::cout << "read : " << filename << std::endl;

// TGA format
// http://www.openspc2.org/format/TGA/index.html

    // image format
	int image_format = header[2];
    std::string format_label = getImageFormatLabel(image_format);
	if( image_format != FORMAT_FULLCOLOR ) {
		std::cout << "unsuported TGA image format: " << format_label << std::endl;
		return false;
	}

	//　Determine width and height
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];

	std::cout << "TGA size: " << width << " x " << height << std::endl;


	//　bit depth
	int bpp = header[16];

	std::cout << "TGA bit depth: " << bpp << std::endl;


    // image descriptor
	char descriptor = header[17];
    int bit_attribute = (0x0f & descriptor);
	int bit_horizontal = (0x10 & descriptor)? 1: 0;
	int bit_vertical = (0x20 & descriptor)? 1: 0;

    printf("TGA descriptor: %x \n", descriptor);

	std::cout << "TGA attribute: " << bit_attribute << std::endl;

    std::string origin_label = getOriginLabel(bit_horizontal, bit_vertical);

	std::cout << "TGA origin: " << origin_label << std::endl;

	// Determine the number of bytes per pixel
	int bytePerPixel = bpp/8;

	// Determination of data size
	int imageRawSize = width * height * bytePerPixel;

	// Allocate memory
	char * imageRawData = new char[imageRawSize];

	// Read pixel data at once
	size_t ret2 = fread(imageRawData, 1, imageRawSize, fp);
    if(ret2 < imageRawSize){
		std::cout << "Could not read image : " << filename << std::endl;
		return false;
    }

	//　Close file
	fclose(fp);

    // get imageData
    imageData =
        alignmentImage(imageRawData, width, height, bpp, bit_vertical);


	delete [] imageRawData;

	return true;
}


/**
 * alignmentImage
 */
char* 
TGAImage::alignmentImage(char *src, int width, int height, int bpp, int bit_vertical)
{

	// convert BGR (A) to RGBA
    // reversr upside down, if origin is bottom

    int bufsize = 4 * width * height;
    char* buff = new char[bufsize];

    int src_index;
    int buf_index;
    char a;

    for(int y = 0;  y<height; y++)
    {
        for(int x = 0; x<width; x++)
        {

            int col     = x;
            int row     = height - y - 1;

            if(bit_vertical==0){
                // origin bottom
                // reverse upside down
                int index_rev  = (row * width + (width - col)) * 4;
                buf_index = bufsize - index_rev;
                if( bpp== 24){
                    src_index   = (row * width + col) * 3;
                }else if( bpp== 32){
                    src_index   = (row * width + col) * 4;
                }
            }else if(bit_vertical==1){
                // origin top
                buf_index   = 4*width*y + 4*x;
                if( bpp== 24){
                    src_index   =  3*width*y + 3*x;
                }else if( bpp== 32){
                    src_index   =  buf_index;
                }
            }

            char b = src[src_index + 0]; // B
            char g = src[src_index + 1]; // G
            char r = src[src_index + 2]; // R

            if( bpp== 24){
                a = (char)255;
            }else if( bpp== 32){
                a= src[src_index + 3]; // A
            }

            buff[buf_index + 0] = r; // R
            buff[buf_index + 1] = g; // G
            buff[buf_index + 2] = b; // B
            buff[buf_index + 3] = a; // A

        } // x
    } // y

    return buff;
}


/**
 * getImageFormatLabel
 */
std::string TGAImage::getImageFormatLabel(int format)
{
    std::string label = "un kown";
    switch(format){
        case 0:
            label = "no image";
            break;
        case 1:
            label = "index color 256";
            break;
        case 2:
            label = "full color";
            break;
        case 3:
            label = "monotone";
            break;
        case 9:
            label = "index color 256 RLE";
            break;
        case 10:
            label = "full color RLE";
            break;
        case 11:
            label = "monotone RLE";
            break;
    }
    return label;
}


/**
 * getOriginLabel
 */
    std::string TGAImage::getOriginLabel(int bit_horizontal, int bit_vertical)
{

    std::string label = "";

    switch(bit_horizontal){
    case 0:
        label += "left ";
        break;
    case 1:
        label += "right ";
        break;
    }

    switch(bit_vertical){
    case 0:
        label += "bottom";
        break;
    case 1:
        label +=  "top";
        break;
    }

    return label;
}
