/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl5.html
 */

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
#include <fstream>
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
	imageSize = 0;
	imageData = NULL;
	format = GL_RGB;
	internalFormat = GL_RGB;
	width = 0;
	height = 0;
	bpp = 0;
	ID = 0;
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
GLubyte* TGAImage::getImageData() {
	return imageData;
}

/** 
 * getImageSize
 */
GLuint TGAImage::getImageSize() {
	return imageSize;
}


/** 
 * getWidth
 */
GLuint TGAImage::getWidth() {
	return width;
}


/** 
 * getHeight
 */
GLuint TGAImage::getHeight() {
	return height;
}


/** 
 * getFormat
 */
GLenum TGAImage::getFormat() {
	return format;
}


/** 
 * getInternalFormat
 */
GLuint TGAImage::getInternalFormat() {
	return internalFormat;
}


/** 
 * getBitDepth
 */
GLuint TGAImage::getBitDepth() {
	return bpp;
}

//---------------------------------------------------------------------------------------------------
//　　ReadTGA
//　　Desc :  Read TGA file
//---------------------------------------------------------------------------------------------------
//bool TGAImage::ReadTGA(const char *filename)
bool TGAImage::ReadTGA(std::string filename)
{

// TGA format
// http://www.openspc2.org/format/TGA/index.html

	//FILE *fp;
	GLubyte header[18]; 
	GLubyte bytePerPixel;
	GLuint temp;

	//　Open file
	//if ( (fp = fopen(filename,"rb")) == NULL )
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

    // image format
	int image_format = header[2];
    std::string format_label = getImageFormatLabel(image_format);
	if( image_format !=FORMAT_FULLCOLOR ) {
		std::cout << "unsuported TGA image format: " << format_label << std::endl;
		return false;
	}

	std::cout << "TGA image format: " << format_label << std::endl;

	//　Determine width and height
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	
	std::cout << "TGA size: " << width << " x " << height << std::endl;

	//　bit depth
	GLuint bpp = header[16];

	std::cout << "TGA bit depth: " << bpp << std::endl;

	//　24 bit
	if ( bpp == 24 )
	{
		format = GL_RGB;
		internalFormat = GL_RGB;
	}
	//　32 bit
	else if ( bpp == 32 )
	{
		format = GL_RGBA;
		internalFormat = GL_RGBA;
	}

	// Determine the number of bytes per pixel
	bytePerPixel = bpp/8;

	// Determination of data size
	imageSize = width * height * bytePerPixel;

	// Allocate memory
	imageData = new GLubyte[imageSize];

	// Read pixel data at once
	size_t ret2 = fread(imageData, 1, imageSize, fp);
    if(ret2 < imageSize){
		std::cout << "Could not read image : " << filename << std::endl;
		return false;
    }

	//　Convert BGR (A) to RGB (A)
	for ( int i=0; i<(int)imageSize; i+=bytePerPixel )
	{
		temp = imageData[i];
		imageData[i+0] = imageData[i+2];
		imageData[i+2] = temp;
	}

	//　Close file
	fclose(fp);

	return true;
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

//---------------------------------------------------------------------------------------------------
//　　Load
//　　Desc : Read TGA file and generate texture
//---------------------------------------------------------------------------------------------------
//GLuint TGAImage::Load(const char *filename)
GLuint TGAImage::Load(std::string filename)
{
	//　Read file
	if ( !ReadTGA(filename) )
		return false;

	//　generate Texture
	glGenTextures(1, &ID);

	//　Bind Texture
	glBindTexture(GL_TEXTURE_2D, ID);

	//　
	if ( bpp == 24 ) glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	else if ( bpp == 32 ) glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//　Texture assignment
	gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height, format, GL_UNSIGNED_BYTE, imageData);

	//　Specifying how to scale the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//　Texture environment
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//　Release memory
	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}
	return ID;
}