/*
 * DDSLoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl7.html
 */

// this smple require OpenGL

/*************************************************************************
　　DDSLoader.cpp

　　Direct Draw Surface Loader

　　Date : Nov. 01, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo :
*************************************************************************/

//
//　include
//
#include "DDSLoader.h"


//　disable Warning C4996
#pragma warning (disable : 4996 )


//////////////////////////////////////////////////////////////////////////
//　　DDSImage
//////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------
//　　DDSImage
//　　Desc : Constructor
//---------------------------------------------------------------------------------------------------
DDSImage::DDSImage()
{
	imageSize = 0;
	imageData = NULL;
	format = GL_RGB;
	internalFormat = GL_RGB;
	width = 0;
	height = 0;
	bpp = 0;
	ID = 0;
	numMipmaps = 0;
    ddsFormat = "";

}

//---------------------------------------------------------------------------------------------------
//　　~DDSImage
//　　Desc : Destructor
//---------------------------------------------------------------------------------------------------
DDSImage::~DDSImage()
{
	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}
}


//---------------------------------------------------------------------------------------------------
//　　DDSImage
//　　Desc : getter
//---------------------------------------------------------------------------------------------------


/** 
 * getWidth
 */
int DDSImage::getWidth() {
	return width;
}

/** 
 * getHeight
 */
int DDSImage::getHeight() {
	return height;
}

/** 
 * getFormat
 */
GLenum DDSImage::getFormat() {
	return format;
}

/** 
 * getDdsFormat
 */
std::string DDSImage::getDdsFormat(){
	return ddsFormat;
}


//---------------------------------------------------------------------------------------------------
//　　ReadFileDDS
//　　Desc : Reading DDS files
//---------------------------------------------------------------------------------------------------
bool DDSImage::ReadDDS(std::string filename)
{
	FILE *fp;
	char magic[4];
	int mipmapFactor;
	long curr, end;
	DDSurfaceDesc ddsd;


	// Open file
	fp = fopen(filename.c_str(), "rb");
	if ( !fp )
	{
		std::cerr << "could not opened file: " << filename << std::endl;
		return false;
	}

	// Read magic
	fread(&magic, sizeof(char), 4, fp);

	// Check the magic
	if ( strncmp(magic, "DDS ", 4 ) != 0 )
	{
		std::cerr << "NOT Support format: " << magic << std::endl;
		fclose(fp);
		return false;
	}

	// Read header
	fread(&ddsd, sizeof(ddsd), 1, fp);

	// Store width and height
	height = ddsd.height;
	width = ddsd.width;
	numMipmaps = ddsd.mipMapLevels;

	// Format determination
GLuint fourCC = ddsd.format.fourCC;
	switch ( fourCC )
	{
	case FOURCC_DXT1:
		//　DXT1
        ddsFormat = "DXT1";
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		internalFormat = 3;
		mipmapFactor = 2;
		break;

	case FOURCC_DXT3:
		//　DXT3
        ddsFormat = "DXT3";
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		internalFormat = 4;
		mipmapFactor = 4;
		break;

	case FOURCC_DXT5:
		//　DXT5
        ddsFormat = "DXT5";
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		internalFormat = 4;
		mipmapFactor = 4;
		break;

	default:
		std::cerr << "NOT format: " << fourCC << std::endl;
		std::cerr << "Use one of DXT1, DXT3, DXT5 " << fourCC << std::endl;
		return false;
	} // switch

	// Calculate pixel data size
	curr = ftell(fp);
	fseek(fp, 0, SEEK_END);
	end = ftell(fp);
	fseek(fp, curr, SEEK_SET);
	imageSize = end - curr;
	imageData = new char [imageSize];

	// Read pixel data
	fread(imageData, sizeof(char), imageSize, fp);

	// Close file
	fclose(fp);

	return true;
}

//-----------------------------------------------------------------------------------------------------
//　　DecompressDDS
//　　Desc : Decompression of  S3TC compression

//-----------------------------------------------------------------------------------------------------
void DDSImage::DecompressDDS()
{
	int blockSize;
	int offset = 0;
	GLsizei mWidth = width, mHeight = height, mSize = 0;

	//　DXT1
	if ( format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
		blockSize = 8;
	//　DXT3, DXT5
	else
		blockSize = 16;

	// Decompress
	for ( int i=0; i<(int)numMipmaps; i++ )
	{
		mSize = ( (mWidth+3)/4 ) * ( (mHeight+3)/4 ) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, i, format, mWidth, mHeight, 0, mSize, imageData + offset );
		
		if ( mWidth >> 1 )	mWidth = (mWidth >> 1);
		else	mWidth = 1;

		if ( mHeight >> 1 )	mHeight = (mHeight >> 1);
		else	mHeight = 1;

		offset += mSize;
	}
}

//---------------------------------------------------------------------------------------------------
//　　Load
//　　Desc : Read DDS file and generate texture
//---------------------------------------------------------------------------------------------------
GLuint DDSImage::Load(std::string filename)
{
	// Read file
	if ( !ReadDDS(filename) )
		return 0;

	// generate texture
	glGenTextures(1, &ID);

	// bind Texture
	glBindTexture(GL_TEXTURE_2D, ID);

	// Specifying how to scale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	// Set texture environment
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Decompress
	DecompressDDS();

	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}

	//
	glBindTexture(GL_TEXTURE_2D, 0);

	// Returns the generated Texture ID
	return ID;
}