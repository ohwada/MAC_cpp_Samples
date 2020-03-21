/**
 * RawLoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl4.html
 */

/*************************************************************************
　　RAWLoader.cpp

　　RAWファイルの読み込み

　　Date : Aug 27, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo : 
**************************************************************************/

//
//　include
//
#include <fstream>

#include "RawLoader.h"

using namespace std;


//////////////////////////////////////////////////////////////////////////
//　　RAWImage class
//////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------------
//　　RAWImage
//　　Desc : コンストラクタ
//----------------------------------------------------------------------------------------------------
RAWImage::RAWImage()
{
	imageSize = 0;
	imageData = NULL;
	//format = GL_RGB;
	//internalFormat = GL_RGB;
	width = 0;
	height = 0;
	bpp = 0;
	//ID = 0;
}

//---------------------------------------------------------------------------------------------------
//　　‾RAWImage
//　　Desc : デストラクタ
//---------------------------------------------------------------------------------------------------
RAWImage::~RAWImage()
{
	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}
}



char* RAWImage::getImageData()
{
	return imageData;
}

int RAWImage::getWidth()
{
	return width;
}

int RAWImage::getHeight()
{
	return height;
}

int RAWImage::getBpp()
{
	return bpp;
}


//---------------------------------------------------------------------------------------------------
//　　ReadRAW
//　　Desc : ファイル読み込み
//---------------------------------------------------------------------------------------------------
//bool RAWImage::ReadRAW(const std::string filename, const GLuint width, const GLuint height, bool alphaFlag)

bool RAWImage::ReadRAW(const std::string filename, const int width, const int height, bool alphaFlag)
{
	ifstream file;

	file.open(filename.c_str(), ios::in | ios::binary);
	if ( !file.is_open() )
	{
		cout << "Error : 指定されたファイルを開けません¥n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	if ( alphaFlag )
	{
		imageSize = width*height*4;
		//format = GL_RGBA;
		//internalFormat = GL_RGBA;
	}
	else
	{
		imageSize = width*height*3;
		//format = GL_RGB;
		//internalFormat = GL_RGB;
	}

	//imageData = new GLubyte [imageSize];
	imageData = new char[imageSize];

	file.read((char*)imageData, imageSize);

	file.close();

	return true;	
}

//---------------------------------------------------------------------------------------------------
//　　Load
//　　Desc : ファイルを読み込みテクスチャを作成
//---------------------------------------------------------------------------------------------------

