/**
 * libtiff Sample
 * 2020-02-01 K.OHWADA
 */

// reference : http://mf-atelier.sakura.ne.jp/mf-atelier/modules/tips/libs/libtiff/libtiff_write_8bit.html

#include <string> 
#include<iostream>
#include <ostream>

#include <tiffio.h>

#include "pixels.h"

using namespace std;



/**
 * saveImage
 */
bool saveImage(string output, char *data, int width, int height)
{
  
// open tiff file
    TIFF *tif = TIFFOpen( output.c_str(), "w" );
    if ( !tif ){
        return false;
    }
  
    if ( TIFFSetField( tif, TIFFTAG_IMAGEWIDTH,width ) != 1 ){
        return false; 
    }

    if ( TIFFSetField( tif, TIFFTAG_IMAGELENGTH, height ) != 1 ){
        return false;
    }

    if ( TIFFSetField( tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE ) != 1 ){
        return false;
    }

    if ( TIFFSetField( tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB ) != 1 ){
        return false;
    }

    if ( TIFFSetField( tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, 0) ) != 1 ){
        return false;      //ストリップあたり行数
    }

    if ( TIFFSetField( tif, TIFFTAG_SAMPLESPERPIXEL, 4 ) != 1 ){
        return false;
    }

    if ( TIFFSetField( tif, TIFFTAG_BITSPERSAMPLE, 8 ) != 1 ){
        return false;
    }

     if ( TIFFSetField( tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG ) != 1 ){
        return false; 
    }

    if ( TIFFSetField( tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT ) != 1 ){
        return false;
    }

  int nRowsPerStrip;
  TIFFGetFieldDefaulted( tif, TIFFTAG_ROWSPERSTRIP, &nRowsPerStrip );

// write strip
    int nStrip = 0;
    char* pData = data;

  for (int i = 0; i < height; i += nRowsPerStrip )
  {
    int nRow = ( i+nRowsPerStrip > height ) ? height - i : nRowsPerStrip;
    int nStripSize = TIFFVStripSize( tif, nRow );
    if ( TIFFWriteEncodedStrip( tif, nStrip++, pData, nStripSize ) < 0 )
    {
      TIFFClose( tif );
      return false;
    }
    pData += nStripSize;
  }
  
// close tiff file
  TIFFClose( tif );

    return true;
}



/**
 * createOutputFileName
 */
string createOutputFileName(int size, int scale)
{

    const char DOT = '.';
    const char UNDERBAR = '_';
    const string EXT = "tif";

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + DOT + EXT;

    return output;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "libpng : write" << endl;


    // 512 x 512
    int size = 2;
    int scale = 256;

    if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] "  << endl;
    }

    // image size
    int width = size * scale;
    int height = size * scale;

    // output file name
    string output = createOutputFileName(size, scale);

    // create Pixel
    char *data = 
        createColorMatrixPixel32(size, scale);

    // save image
    bool ret = saveImage(output, data, width, height);
    if(ret){
            cout << "saved Image: " << output << endl;
    }else{
            cerr << "saved Image Faild: " << output << endl;
            return EXIT_FAILURE;
    }


	return EXIT_SUCCESS;
}

