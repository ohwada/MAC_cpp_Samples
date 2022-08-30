pngriter: setup
===============


### Require  
-  libpng  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libpng

- freetype  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/FreeType  


### Download
% git clone https://github.com/pngwriter/pngwriter

### Install  
#### method 1  
build Your file with pngwriter.cc  
copy pngwriter.cc pngwriter.h to Your directory  

#### method 2  
create shared libraly (libpngwriter.a) 

##### method 2-1  
build with the enclosed CMakeLists.txt  
% mkdir build  
% cd build
% cmake ..
% make

TODO:  
build with shared library and run, the error below  
> libpng warning: Application built with libpng-1.4.12 but running with 1.6.37  

##### method 2-2  
build with self-made Makefile

(1) create shared libraly (libpngwriter.a) 
copy Makefile to downloaded directory (pngwriter)  
% mkdir lib  
% make  

(2) copy header files and lib files to system area 
(eg /usr/local/opt/pngriter)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(3) copy config file (pngwriter.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs pngwriter

(4) copy libpngwriter.a to lib/

TODO:  
build with shared library and run, the error below  
> dyld: Library not loaded: lib/libpngwriter.a

