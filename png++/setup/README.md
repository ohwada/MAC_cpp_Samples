png++ setup
===============


### Require  
-  libpng  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libpng

### Install  
(1) % brew install png++  
https://formulae.brew.sh/formula/png++  

% ls /usr/local/include/png++  

(2) copy config file (pngpp.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs pngpp
