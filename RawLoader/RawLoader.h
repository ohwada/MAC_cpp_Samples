/**
 * RawLoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl4.html
 */

/************************************************************************
　　RawLoader.h

　　RAWファイルを読み込む

　　Date : Aug 27, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo :
*************************************************************************/

#ifndef _RAW_LOADER_H_INCLUDED_
#define _RAW_LOADER_H_INCLUDED_

//
//　include
//
#include <string>
#include <iostream>


// macOS
//#include <OpenGL/OpenGL.h>
//#include <GLUT/glut.h>


using namespace std;

//////////////////////////////////////////////////////////////////////////
//　　RAWImage class
//////////////////////////////////////////////////////////////////////////
class RAWImage
{
protected:
	//GLuint imageSize;
	//GLubyte *imageData;
	//GLenum format;
	//GLuint internalFormat;
	//GLuint width;
	//GLuint height;
	//GLuint bpp;

	int imageSize;
	char *imageData;
	//GLenum format;
	//GLuint internalFormat;
	int width;
	int height;
	int bpp;

public:
	//GLuint ID;
	RAWImage();
	~RAWImage();
	//bool ReadRAW(const std::string filename, const GLuint width, const GLuint height, bool alphaFlag=false);
	//bool Load(const std::string filename, const GLuint width, const GLuint height, bool alphaFlag=false);

	bool ReadRAW(const std::string filename, const int width, const int height, bool alphaFlag=false);

	//bool Load(const std::string filename, const int width, const int height, bool alphaFlag=false);

char* getImageData();
int getWidth();
int getHeight();
int getBpp();

};


#endif	//　_RAW_LOADER_H_INCLUDED_