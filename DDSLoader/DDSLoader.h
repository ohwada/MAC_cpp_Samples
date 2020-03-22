/*
 * DDSLoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl7.html
 */


/*************************************************************************
　　DDSLoader.h　

　　Direct Draw Surface Loader

　　Date : Nov 01, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo : DDSファイルを読み込むためにGLEWを使用します
*************************************************************************/

#ifndef _DDS_LOADER_H_INCLUDED_
#define _DDS_LOADER_H_INCLUDED_

//
//　include
//
#include <string>
#include <iostream>
#include <fstream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>


//
//　define
//
#define FOURCC_DXT1 '1TXD'
#define FOURCC_DXT3 '3TXD'
#define FOURCC_DXT5 '5TXD'

//
//　struct
//

typedef struct _DDPixelFormat
{
	GLuint size;
	GLuint flgas;
	GLuint fourCC;
	GLuint bpp;
	GLuint redMask;
	GLuint greenMask;
	GLuint blueMask;
	GLuint alphaMask;
} DDPixelFormat;

typedef struct _DDSCaps
{
	GLuint caps;
	GLuint caps2;
	GLuint caps3;
	GLuint caps4;
} DDSCaps;

typedef struct _DDColorKey
{
	GLuint lowVal;
	GLuint highVal;
} DDColorKey;

typedef struct _DDSurfaceDesc
{
	GLuint size;
	GLuint flags;
	GLuint height;
	GLuint width;
	GLuint pitch;
	GLuint depth;
	GLuint mipMapLevels;
	GLuint alphaBitDepth;
	GLuint reserved;
	GLuint surface;

	DDColorKey ckDestOverlay;
	DDColorKey ckDestBlt;
	DDColorKey ckSrcOverlay;
	DDColorKey ckSrcBlt;

	DDPixelFormat format;
	DDSCaps caps;

	GLuint textureStage;
} DDSurfaceDesc;


//////////////////////////////////////////////////////////////////////////
//　　DDSImage class
//////////////////////////////////////////////////////////////////////////
class DDSImage
{
protected:
	int imageSize;
	char *imageData;
	GLenum format;
	GLuint internalFormat;
	int width;
	int height;
	int bpp;

	int numMipmaps;
    std::string ddsFormat;

public:
	GLuint ID;
	DDSImage();
	~DDSImage();
	void DecompressDDS();
	bool ReadDDS(std::string filename);
	GLuint Load(std::string filename);
	int getWidth();
	int getHeight();
	GLenum getFormat();
	std::string getDdsFormat();

};

#endif	//　_DDS_LOADER_H_INCLUDED_