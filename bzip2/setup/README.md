bzip2: setup
===============


### Install 
(1) % brew install bzip2  
https://formulae.brew.sh/formula/bzip2  

(2) copy config file (bzip2.pc) to system area (/usr/local/opt/bzip2)
% bash setup.sh
% pkg-config --cflags --libs bzip2

