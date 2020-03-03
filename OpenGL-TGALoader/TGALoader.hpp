/*
 * OpenGL Sample
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

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>



//////////////////////////////////////////////////////////////////////////
//　　TGALoader class
//////////////////////////////////////////////////////////////////////////
class TGAImage
{
protected:
	GLuint imageSize;
	GLubyte *imageData;
	GLenum format;
	GLuint internalFormat;
	GLuint width;
	GLuint height;
	GLuint bpp;
	const int FORMAT_FULLCOLOR = 2;

public:
	GLuint ID;
	TGAImage();
	~TGAImage();
	GLubyte* getImageData();
	GLuint getImageSize();
	GLuint getWidth();
	GLuint getHeight();
	GLenum getFormat();
	GLuint getInternalFormat();
	GLuint getBitDepth();
	bool ReadTGA(std::string filename);
	std::string getImageFormatLabel(int format);
	GLuint Load(std::string filename);
};

#endif		//　_TGA_LOADER_H_INCLUDED_