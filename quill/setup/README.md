quill: setup
===============

setup for quill


###  install  
% brew install quill  
https://formulae.brew.sh/formula/quill
  
https://github.com/odygrd/quill


###  set up for pkg-config  
% bash setup_pkgconfig.sh  

check for pkg-config  
% pkg-config --cflags --libs quill
 -I/usr/local/Cellar/quill/2.5.1/include -L/usr/local/Cellar/quill/2.5.1/lib -lquill -lpthread

