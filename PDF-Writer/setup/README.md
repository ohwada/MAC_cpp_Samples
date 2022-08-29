PDF-Writer: setup
===============


### Require  
-  libpng  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libpng

- libjpeg  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libjpeg

- libtiff  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libtiff

- freetype  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/FreeType  

- zlib  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/zlib


### Install
(1) download souce files  
git clone https://github.com/galkahana/PDF-Writer

(2) Create libPDFWriter.a  
cd downloaded directory (PDF-Writer)  
% mkdir build  
% cd build  
% cmake ..  
% make  


(3) copy header files and lib files to system area 
(eg /usr/local/opt/PDFWriter)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (pdfwriter.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs pdfwriter

